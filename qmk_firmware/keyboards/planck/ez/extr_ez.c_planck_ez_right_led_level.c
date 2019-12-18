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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PWMD4 ; 
 int /*<<< orphan*/  PWM_FRACTION_TO_WIDTH (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ cie_lightness (int) ; 
 int planck_ez_right_led_duty ; 
 int /*<<< orphan*/  pwmDisableChannel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pwmEnableChannel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void planck_ez_right_led_level(uint8_t level) {
    planck_ez_right_led_duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t) level / 255));
    if (level == 0) {
        // Turn backlight off
        pwmDisableChannel(&PWMD4, 2);
    } else {
        // Turn backlight on
        pwmEnableChannel(&PWMD4, 2, PWM_FRACTION_TO_WIDTH(&PWMD4,0xFFFF,planck_ez_right_led_duty));
    }
}