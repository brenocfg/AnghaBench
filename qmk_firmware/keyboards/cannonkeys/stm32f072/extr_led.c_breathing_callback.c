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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  PWMDriver ;

/* Variables and functions */
 scalar_t__ BREATHING_HALT_OFF ; 
 scalar_t__ BREATHING_HALT_ON ; 
 int BREATHING_STEPS ; 
 int /*<<< orphan*/  PWMD3 ; 
 int /*<<< orphan*/  PWM_FRACTION_TO_WIDTH (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int breathing_counter ; 
 scalar_t__ breathing_halt ; 
 int /*<<< orphan*/  breathing_interrupt_disable () ; 
 int breathing_period ; 
 int* breathing_table ; 
 int /*<<< orphan*/  chSysLockFromISR () ; 
 int /*<<< orphan*/  chSysUnlockFromISR () ; 
 int /*<<< orphan*/  cie_lightness (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwmEnableChannelI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_backlight (int) ; 

__attribute__((used)) static void breathing_callback(PWMDriver *pwmp)
{
  (void)pwmp;
  uint16_t interval = (uint16_t) breathing_period * 256 / BREATHING_STEPS;
  // resetting after one period to prevent ugly reset at overflow.
  breathing_counter = (breathing_counter + 1) % (breathing_period * 256);
  uint8_t index = breathing_counter / interval % BREATHING_STEPS;

  if (((breathing_halt == BREATHING_HALT_ON) && (index == BREATHING_STEPS / 2)) ||
      ((breathing_halt == BREATHING_HALT_OFF) && (index == BREATHING_STEPS - 1)))
  {
      breathing_interrupt_disable();
  }

  uint32_t duty = cie_lightness(scale_backlight(breathing_table[index] * 256));

  chSysLockFromISR();
  pwmEnableChannelI(
    &PWMD3,
    0,
    PWM_FRACTION_TO_WIDTH(
      &PWMD3,
      0xFFFF,
      duty
    )
  );
  chSysUnlockFromISR();
}