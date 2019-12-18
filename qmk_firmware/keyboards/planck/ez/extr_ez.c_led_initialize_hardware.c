#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ led_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  PAL_MODE_ALTERNATE (int) ; 
 int /*<<< orphan*/  PWMD4 ; 
 TYPE_1__ keyboard_config ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  planck_ez_left_led_level (int) ; 
 int /*<<< orphan*/  planck_ez_left_led_off () ; 
 int /*<<< orphan*/  planck_ez_right_led_level (int) ; 
 int /*<<< orphan*/  planck_ez_right_led_off () ; 
 int /*<<< orphan*/  pwmCFG ; 
 int /*<<< orphan*/  pwmStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void led_initialize_hardware(void) {
    pwmStart(&PWMD4, &pwmCFG);

    // set up defaults
    planck_ez_right_led_level((uint8_t)keyboard_config.led_level * 255 / 4 );
    palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(2));
    planck_ez_left_led_level((uint8_t)keyboard_config.led_level * 255 / 4 );
    palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(2));


    // turn LEDs off by default
    planck_ez_left_led_off();
    planck_ez_right_led_off();
}