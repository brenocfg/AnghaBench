#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int input_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KC_ENTER ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_SPC ; 
#define  UC_LNX 131 
#define  UC_OSX 130 
#define  UC_WIN 129 
#define  UC_WINC 128 
 int /*<<< orphan*/  UNICODE_KEY_OSX ; 
 int /*<<< orphan*/  set_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 TYPE_1__ unicode_config ; 
 int /*<<< orphan*/  unicode_saved_mods ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

__attribute__((weak)) void unicode_input_finish(void) {
    switch (unicode_config.input_mode) {
        case UC_OSX:
            unregister_code(UNICODE_KEY_OSX);
            break;
        case UC_LNX:
            tap_code(KC_SPC);
            break;
        case UC_WIN:
            unregister_code(KC_LALT);
            break;
        case UC_WINC:
            tap_code(KC_ENTER);
            break;
    }

    set_mods(unicode_saved_mods);  // Reregister previously set mods
}