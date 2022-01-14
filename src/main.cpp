
#include <SPI.h>


char trigger;
uint16_t azimuth;

byte LB ;            // holds the low byte returned from slave
byte HB ;            // ditto highbyte
byte dummy ;

int loopcount = 1;

void setup ()
{
  digitalWrite(SS, HIGH);  // Set SS high
  Serial.begin(9600);
  HB = 0;
  LB = 0;

  delay(1000);  // for serial setup

  SPI.begin();
}


void loop ()
{


  // this code sets up the SPI and sends a trigger character 'H' or 'L' to the slave
  // it receives two bytes representing low and high bytes of a 16 bit unsigned int and assembles them to form the uint16_t


  // configure the SPI settings
  SPI.beginTransaction (SPISettings (2000000, MSBFIRST, SPI_MODE0));   // 2 meg clock

  // enable Slave Select
  digitalWrite(SS, LOW);              // SS is active LOW
  
  trigger = 'A';
  dummy = SPI.transfer(trigger);      // this returns whatever happened to be in the SPDR
  delayMicroseconds(20);              // propagation delay required by SPI

  trigger = 'L';
  LB = SPI.transfer(trigger);         // this returns the low byte
  delayMicroseconds(20);              // propagation delay required by SPI

  trigger = 'H';
  HB = SPI.transfer(trigger);         // this returns the high byte
  delayMicroseconds(20);              // propagation delay required by SPI

  // disable Slave Select
  digitalWrite(SS, HIGH);

  // turn SPI hardware off
  SPI.endTransaction ();              // transaction over

  SPI.end();
  azimuth = (HB << 8) | LB ;          // push the highbyte value 8 bits left to occupy the high 8 bits of the 16 bit int

  Serial.print("loop number  ");
  Serial.println(loopcount);

  Serial.print("low byte value is  ");
  Serial.println(LB);
  Serial.print("High byte value is ");
  Serial.println(HB);
  Serial.print("azimuth is ");
  Serial.println(azimuth);
  loopcount ++;
  delay(1000);

} // end void loop