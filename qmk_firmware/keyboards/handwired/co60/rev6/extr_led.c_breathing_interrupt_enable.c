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
 int /*<<< orphan*/  PWMD4 ; 
 int /*<<< orphan*/  PWM_FRACTION_TO_WIDTH (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  chSysLockFromISR () ; 
 int /*<<< orphan*/  chSysUnlockFromISR () ; 
 int /*<<< orphan*/  pwmCFG_breathing ; 
 int /*<<< orphan*/  pwmEnableChannelI (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwmEnablePeriodicNotification (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwmStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwmStop (int /*<<< orphan*/ *) ; 

void breathing_interrupt_enable(void){
    pwmStop(&PWMD4);
    pwmStart(&PWMD4, &pwmCFG_breathing);
    chSysLockFromISR();
    pwmEnablePeriodicNotification(&PWMD4);
    pwmEnableChannelI(
      &PWMD4,
      2,
      PWM_FRACTION_TO_WIDTH(
        &PWMD4,
        0xFFFF,
        0xFFFF
      )
    );
    chSysUnlockFromISR();
}