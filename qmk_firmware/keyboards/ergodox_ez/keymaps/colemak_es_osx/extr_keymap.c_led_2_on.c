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
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_led_value ; 

void led_2_on(void) {
    ergodox_right_led_2_on();
    ergodox_right_led_2_set(max_led_value);
}