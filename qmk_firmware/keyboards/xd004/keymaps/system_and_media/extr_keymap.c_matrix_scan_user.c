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
 scalar_t__ SUPER_ALT_F4_TIMER ; 
 int /*<<< orphan*/  alt_f4_timer ; 
 int is_alt_f4_active ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 

void matrix_scan_user(void) {
    if (is_alt_f4_active && timer_elapsed(alt_f4_timer) > SUPER_ALT_F4_TIMER) {
        is_alt_f4_active = false;
    }
}