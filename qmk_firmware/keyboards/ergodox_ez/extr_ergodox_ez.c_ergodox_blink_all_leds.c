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
 int /*<<< orphan*/  LED_BRIGHTNESS_DEFAULT ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  ergodox_led_all_off () ; 
 int /*<<< orphan*/  ergodox_led_all_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_left_led_1_off () ; 
 int /*<<< orphan*/  ergodox_left_led_1_on () ; 
 int /*<<< orphan*/  ergodox_left_led_2_off () ; 
 int /*<<< orphan*/  ergodox_left_led_2_on () ; 
 int /*<<< orphan*/  ergodox_left_led_3_off () ; 
 int /*<<< orphan*/  ergodox_left_led_3_on () ; 
 scalar_t__ ergodox_left_leds_update () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 scalar_t__ mcp23018_status ; 

void ergodox_blink_all_leds(void)
{
    ergodox_led_all_off();
    ergodox_led_all_set(LED_BRIGHTNESS_DEFAULT);
    ergodox_right_led_1_on();
    _delay_ms(50);
    ergodox_right_led_2_on();
    _delay_ms(50);
    ergodox_right_led_3_on();
    _delay_ms(50);
#ifdef LEFT_LEDS
    ergodox_left_led_1_on();
    _delay_ms(50);
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
    ergodox_left_led_2_on();
    _delay_ms(50);
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
    ergodox_left_led_3_on();
    _delay_ms(50);
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
#endif
    ergodox_right_led_1_off();
    _delay_ms(50);
    ergodox_right_led_2_off();
    _delay_ms(50);
    ergodox_right_led_3_off();
#ifdef LEFT_LEDS
    _delay_ms(50);
    ergodox_left_led_1_off();
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
    _delay_ms(50);
    ergodox_left_led_2_off();
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
    _delay_ms(50);
    ergodox_left_led_3_off();
    if (!mcp23018_status) {
      mcp23018_status = ergodox_left_leds_update();
    }
#endif

    //ergodox_led_all_on();
    //_delay_ms(333);
    ergodox_led_all_off();
}