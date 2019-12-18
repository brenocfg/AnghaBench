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
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_SPC ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int get_mods () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 scalar_t__ spam_space ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void matrix_scan_user(void) {
    if(spam_space && !(get_mods() & (MOD_BIT(KC_LGUI)))){
        register_code(KC_SPC);
        unregister_code(KC_SPC);
    }
}