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
 int _FNAV ; 
 int _MEDIA ; 
 int _NUMPAD ; 
 int /*<<< orphan*/  chThdSleepMilliseconds (int) ; 
 int /*<<< orphan*/  led_controller_init () ; 
 int /*<<< orphan*/  led_game ; 
 int /*<<< orphan*/  led_media ; 
 int /*<<< orphan*/  led_nav ; 
 int /*<<< orphan*/  led_numpad ; 
 int /*<<< orphan*/  write_led_page (int,int /*<<< orphan*/ ,int) ; 

void matrix_init_user(void) {

    led_controller_init();

    // Write predefined led pages.
    write_led_page(_NUMPAD, led_numpad, 16);
    chThdSleepMilliseconds(10);

    write_led_page(_FNAV, led_nav, 12);
    chThdSleepMilliseconds(10);

    write_led_page(_MEDIA, led_media, 15);
    chThdSleepMilliseconds(10);

    write_led_page(4, led_game, 5);
    chThdSleepMilliseconds(1000);
}