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
 int /*<<< orphan*/  LED_BRIGHTNESS_HI ; 
 int /*<<< orphan*/  frenchdev_led_1_off () ; 
 int /*<<< orphan*/  frenchdev_led_1_on () ; 
 int /*<<< orphan*/  frenchdev_led_2_off () ; 
 int /*<<< orphan*/  frenchdev_led_2_on () ; 
 int /*<<< orphan*/  frenchdev_led_3_off () ; 
 int /*<<< orphan*/  frenchdev_led_3_on () ; 
 int /*<<< orphan*/  frenchdev_led_all_off () ; 
 int /*<<< orphan*/  frenchdev_led_all_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void frenchdev_blink_all_leds(void)
{
    frenchdev_led_all_off();
    frenchdev_led_all_set(LED_BRIGHTNESS_HI);
    frenchdev_led_1_on();
    wait_ms(50);
    frenchdev_led_2_on();
    wait_ms(50);
    frenchdev_led_3_on();
    wait_ms(50);
    frenchdev_led_1_off();
    wait_ms(50);
    frenchdev_led_2_off();
    wait_ms(50);
    frenchdev_led_3_off();
    frenchdev_led_all_off();
}