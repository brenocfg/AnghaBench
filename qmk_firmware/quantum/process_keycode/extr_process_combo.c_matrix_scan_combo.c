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
 scalar_t__ COMBO_TERM ; 
 scalar_t__ b_combo_enable ; 
 int /*<<< orphan*/  dump_key_buffer (int) ; 
 int is_active ; 
 scalar_t__ timer ; 
 scalar_t__ timer_elapsed (scalar_t__) ; 

void matrix_scan_combo(void) {
    if (b_combo_enable && is_active && timer && timer_elapsed(timer) > COMBO_TERM) {
        /* This disables the combo, meaning key events for this
         * combo will be handled by the next processors in the chain
         */
        is_active = false;
        dump_key_buffer(true);
    }
}