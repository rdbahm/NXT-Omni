#pragma config(Sensor, S1,     Touch,               sensorTouch)
#pragma config(Sensor, S2,     Sound,               sensorSoundDB)
#pragma config(Sensor, S3,     Light,               sensorLightActive)
#pragma config(Sensor, S4,     Sonar,               sensorSONAR)
#pragma config(Motor,  motorA,          A,             tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          B,             tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          C,             tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*****Omni NXT Bot*****/
/*   Ryan Bahm   	  */
/*   11/19/2010       */
/**********************/

//Variables Global
int Run = 1;
//Movement-------
int SpeedA = 0;
int SpeedB = 0;
int SpeedC = 0;

int Direction = 0;
int Speed = 100; // Allows user to stop all movement, including spin.

int Spin = 0;

int MaxSpeed = 100; //The maximum speed we want to go, including spin. Changing to 0 will not stop spinning.

int CompleteSpin = 2000; //2 Seconds for a complete spin at 100%. Entered in 1000ths of a second.
int MinDegree = 4; //The number of degrees before we make a correction for spin.
int OneDeg = (CompleteSpin)/360; // The amount of time it takes to go one degree.
int TimeElapsed=0;
//------------------






task MotorControl()
{
  //NXT OmniBot Motor Control Basecode
  //Ryan Bahm
  //V2.0

  ClearTimer(T1);

  while (Run ==1)
  {

    //Code to bring erroneous direction values back in range.
    if(Direction < 0)
    {
      Direction = 360+Direction;
    }
    else if(Direction > 360)
    {
      Direction = Direction-360;
    }


    //Code to determine motor direction.
    //Trig to determine motor driving speed. Deduct amount of desired spin from movement, so we can always spin.
    SpeedA =  (MaxSpeed-abs(Spin))*cosDegrees(Direction-150);
    SpeedB =  (MaxSpeed-abs(Spin))*cosDegrees(Direction+90);
    SpeedC =  (MaxSpeed-abs(Spin))*cosDegrees(Direction-30);

    //Add spin amount to motor control.
    SpeedA = SpeedA+Spin;
    SpeedB = SpeedB+Spin;
    SpeedC = SpeedC+Spin;

    //Change speed by user-entered amount.
    SpeedA = SpeedA*(Speed/100);
    SpeedB = SpeedB*(Speed/100);
    SpeedC = SpeedC*(Speed/100);

    motor[A] = SpeedA;
    motor[B] = SpeedB;
    motor[C] = SpeedC;

    TimeElapsed = time1[T1]; //How much time has elapsed since the last cycle?

    if(TimeElapsed >= OneDeg * (100/abs(Spin)) * MinDegree && Spin != 0) //We have to wait until we've at least changed directions by MinDegree degrees.
    {
    //NewDirection = Direction - ( ( (TimeElapsed * SpinCorrectionQuotient)/1000) * (Spin/100) ); //Corrects for spin while moving forward.
      if(Spin > 0)
      {
      Direction = Direction-MinDegree;
      }

      if(Spin < 0)
      {
      Direction = Direction+MinDegree;
      }

      ClearTimer(T1);

    }

  }


}



task main()
{
  StartTask(MotorControl);

  Direction = 0;
  Speed = 100;
  Spin = 25;




}
