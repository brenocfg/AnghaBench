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
 int /*<<< orphan*/  dk60_led_all_off () ; 
 int /*<<< orphan*/  dk60_led_all_on () ; 

void dk60_blink_all_leds(void)
{
    dk60_led_all_off();
    dk60_led_all_on();
    _delay_ms(500);
    dk60_led_all_off();
}