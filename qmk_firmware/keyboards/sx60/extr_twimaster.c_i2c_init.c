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

/* Variables and functions */
 int TWBR ; 
 scalar_t__ TWSR ; 

void i2c_init(void)
{
  /* initialize TWI clock
   * minimal values in Bit Rate Register (TWBR) and minimal Prescaler
   * bits in the TWI Status Register should give us maximal possible
   * I2C bus speed - about 444 kHz
   *
   * for more details, see 20.5.2 in ATmega16/32 secification
   */

  TWSR = 0;     /* no prescaler */
  TWBR = 10;    /* must be >= 10 for stable operation */

}