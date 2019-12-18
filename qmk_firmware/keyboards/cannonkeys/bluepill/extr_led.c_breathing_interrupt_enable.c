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
 int /*<<< orphan*/  PWMD1 ; 
 int /*<<< orphan*/  PWM_FRACTION_TO_WIDTH (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  chSysLockFromISR () ; 
 int /*<<< orphan*/  chSysUnlockFromISR () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pwmCFG_breathing ; 
 int /*<<< orphan*/  pwmEnableChannelI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwmEnablePeriodicNotification (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwmStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwmStop (int /*<<< orphan*/ *) ; 

void breathing_interrupt_enable(void){
    pwmStop(&PWMD1);
    printf("starting with callback\n");
    pwmStart(&PWMD1, &pwmCFG_breathing);
    chSysLockFromISR();
    pwmEnablePeriodicNotification(&PWMD1);
    pwmEnableChannelI(
      &PWMD1,
      0,
      PWM_FRACTION_TO_WIDTH(
        &PWMD1,
        0xFFFF,
        0xFFFF
      )
    );
    chSysUnlockFromISR();
}