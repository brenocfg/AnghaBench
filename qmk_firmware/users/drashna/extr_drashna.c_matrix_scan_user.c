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
 int /*<<< orphan*/  matrix_scan_keymap () ; 
 int /*<<< orphan*/  matrix_scan_rgb () ; 
 int /*<<< orphan*/  run_diablo_macro_check () ; 
 int /*<<< orphan*/  startup_user () ; 

void matrix_scan_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }

#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
    run_diablo_macro_check();
#endif  // TAP_DANCE_ENABLE

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    matrix_scan_rgb();
#endif  // RGBLIGHT_ENABLE

    matrix_scan_keymap();
}