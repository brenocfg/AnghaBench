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
 int /*<<< orphan*/  ergodox_board_led_1_off () ; 
 int /*<<< orphan*/  ergodox_board_led_1_on () ; 
 int /*<<< orphan*/  ergodox_board_led_2_off () ; 
 int /*<<< orphan*/  ergodox_board_led_2_on () ; 
 int /*<<< orphan*/  ergodox_board_led_3_off () ; 
 int /*<<< orphan*/  ergodox_board_led_3_on () ; 
 int /*<<< orphan*/  ergodox_led_all_off () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void ergodox_blink_all_leds(void)
{
    ergodox_led_all_off();
    // ergodox_led_all_set(LED_BRIGHTNESS_DEFAULT);
    ergodox_board_led_1_on();
    wait_ms(50);
    ergodox_board_led_2_on();
    wait_ms(50);
    ergodox_board_led_3_on();
    wait_ms(50);
    ergodox_board_led_1_off();
    wait_ms(50);
    ergodox_board_led_2_off();
    wait_ms(50);
    ergodox_board_led_3_off();
}