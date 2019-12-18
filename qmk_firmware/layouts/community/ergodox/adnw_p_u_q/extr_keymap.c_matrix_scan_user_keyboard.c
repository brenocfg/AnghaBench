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
 int /*<<< orphan*/  ergodox_board_led_on () ; 
 int /*<<< orphan*/  ergodox_led_all_on () ; 

void matrix_scan_user_keyboard(void) {
    ergodox_board_led_on();
    ergodox_led_all_on();
}