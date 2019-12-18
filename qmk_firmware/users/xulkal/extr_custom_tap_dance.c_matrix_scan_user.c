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
 scalar_t__ KC_TRANSPARENT ; 
 int /*<<< orphan*/  run_custom_tap_dance (int /*<<< orphan*/ ) ; 
 scalar_t__ td_keycode ; 
 int /*<<< orphan*/  td_timer ; 
 scalar_t__ timer_expired (int /*<<< orphan*/ ) ; 

void matrix_scan_user(void)
{
    if (td_keycode != KC_TRANSPARENT && timer_expired(td_timer))
        run_custom_tap_dance(0);
}