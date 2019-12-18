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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ TAPPING_TERM ; 
 int last_mod ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_timer ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void mod_lift(uint16_t tap_code, uint16_t hold_code, int id) {
    unregister_code(hold_code);
    if (last_mod == id && timer_elapsed(tap_timer) < TAPPING_TERM) {
        tap_code16(tap_code);
        last_mod = 10;
    }
}