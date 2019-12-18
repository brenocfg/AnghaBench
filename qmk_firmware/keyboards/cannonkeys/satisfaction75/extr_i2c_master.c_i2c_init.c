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
 int /*<<< orphan*/  GPIOB ; 
 int PAL_MODE_ALTERNATE (int) ; 
 int PAL_MODE_INPUT ; 
 int PAL_STM32_OTYPE_OPENDRAIN ; 
 int /*<<< orphan*/  chThdSleepMilliseconds (int) ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int) ; 

__attribute__ ((weak))
void i2c_init(void)
{
  // Try releasing special pins for a short time
  palSetPadMode(GPIOB, 6, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 7, PAL_MODE_INPUT);

  chThdSleepMilliseconds(10);

  palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(1) | PAL_STM32_OTYPE_OPENDRAIN);
  palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(1) | PAL_STM32_OTYPE_OPENDRAIN);

  //i2cInit(); //This is invoked by halInit() so no need to redo it.
}