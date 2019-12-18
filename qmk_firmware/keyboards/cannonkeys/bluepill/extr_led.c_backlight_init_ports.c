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
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  PAL_MODE_STM32_ALTERNATE_PUSHPULL ; 
 int /*<<< orphan*/  PWMD1 ; 
 int /*<<< orphan*/  PWM_FRACTION_TO_WIDTH (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cie_lightness (int) ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pwmCFG ; 
 int /*<<< orphan*/  pwmEnableChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwmStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void backlight_init_ports(void) {
    printf("backlight_init_ports()\n");
    #ifdef BACKLIGHT_ENABLE

    palSetPadMode(GPIOA, 8, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    pwmStart(&PWMD1, &pwmCFG);
    pwmEnableChannel(&PWMD1, 0, PWM_FRACTION_TO_WIDTH(&PWMD1, 0xFFFF,cie_lightness(0xFFFF)));
    #endif
}