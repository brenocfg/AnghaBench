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
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  all_led_off () ; 
 int /*<<< orphan*/  all_led_on () ; 
 int /*<<< orphan*/  caps_lock_led_on () ; 
 int /*<<< orphan*/  keypad_led_on () ; 
 int /*<<< orphan*/  num_lock_led_on () ; 
 int /*<<< orphan*/  scroll_lock_led_on () ; 

void blink_all_leds(void)
{
        all_led_on();
        _delay_ms(500);

        all_led_off();
        _delay_ms(100);

        caps_lock_led_on();
        _delay_ms(100);

	 num_lock_led_on();
        _delay_ms(100);

        scroll_lock_led_on();
        _delay_ms(100);

         keypad_led_on();
        _delay_ms(100);

        //back

        scroll_lock_led_on();
        _delay_ms(100);

        num_lock_led_on();
        _delay_ms(100);

        caps_lock_led_on();
        _delay_ms(100);

        all_led_off();
}