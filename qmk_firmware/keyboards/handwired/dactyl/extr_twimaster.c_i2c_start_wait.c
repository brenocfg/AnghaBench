#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;

/* Variables and functions */
 int TWCR ; 
 unsigned char TWDR ; 
 int TWEN ; 
 int TWINT ; 
 int TWSTA ; 
 int TWSTO ; 
 int TW_MR_DATA_NACK ; 
 int TW_MT_SLA_NACK ; 
 int TW_REP_START ; 
 int TW_START ; 
 int TW_STATUS ; 

void i2c_start_wait(unsigned char address)
{
    uint8_t   twst;


    while ( 1 )
    {
      // send START condition
      TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

      // wait until transmission completed
      while(!(TWCR & (1<<TWINT)));

      // check value of TWI Status Register. Mask prescaler bits.
      twst = TW_STATUS & 0xF8;
      if ( (twst != TW_START) && (twst != TW_REP_START)) continue;

      // send device address
      TWDR = address;
      TWCR = (1<<TWINT) | (1<<TWEN);

      // wail until transmission completed
      while(!(TWCR & (1<<TWINT)));

      // check value of TWI Status Register. Mask prescaler bits.
      twst = TW_STATUS & 0xF8;
      if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
      {
          /* device busy, send stop condition to terminate write operation */
          TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

          // wait until stop condition is executed and bus released
          while(TWCR & (1<<TWSTO));

          continue;
      }
      //if( twst != TW_MT_SLA_ACK) return 1;
      break;
     }

}