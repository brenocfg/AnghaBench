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
 int /*<<< orphan*/  PWM_FRACTION_TO_WIDTH (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  planck_ez_left_led_duty ; 
 int /*<<< orphan*/  pwmEnableChannel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void planck_ez_left_led_on(void){
    pwmEnableChannel(&PWMD4, 3, PWM_FRACTION_TO_WIDTH(&PWMD4,0xFFFF,planck_ez_left_led_duty));
}