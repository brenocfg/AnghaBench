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
 int /*<<< orphan*/  UC_WINC ; 
 int /*<<< orphan*/  matrix_init_keymap () ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 

void matrix_init_user(void) {
    #ifdef UNICODEMAP_ENABLE
    // Set Unicode input to use WinCompose
    // https://github.com/samhocevar/wincompose
    set_unicode_input_mode(UC_WINC);
    #endif // UNICODEMAP_ENABLE

    matrix_init_keymap();
}