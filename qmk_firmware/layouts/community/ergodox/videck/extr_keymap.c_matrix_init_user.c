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
 int /*<<< orphan*/  LED_BRIGHTNESS_LO ; 
 int caps_lock_is_on ; 
 int /*<<< orphan*/  ergodox_led_all_set (int /*<<< orphan*/ ) ; 

void matrix_init_user(void) {
  ergodox_led_all_set(LED_BRIGHTNESS_LO);
  caps_lock_is_on = false;
}