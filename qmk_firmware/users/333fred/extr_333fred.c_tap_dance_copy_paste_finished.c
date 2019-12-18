#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int MOD_MASK_SHIFT ; 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_LCTRL (char*) ; 
 int /*<<< orphan*/  SS_LSFT (char*) ; 
 char* SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_INSERT ; 
 int get_mods () ; 
 int get_oneshot_mods () ; 
 int /*<<< orphan*/  set_oneshot_mods (int) ; 

void tap_dance_copy_paste_finished(qk_tap_dance_state_t *state, void *user_data) {
    bool is_paste = state->count == 2;
    // If either the one-shot shift is set, or if shift is being held, count as shift being held.
    // We'll clear the one-shot shift if it was held
    uint8_t one_shot_mods = get_oneshot_mods();
    bool is_shift = false;

    if (get_mods() & MOD_MASK_SHIFT) {
        is_shift = true;
    } else if (one_shot_mods & MOD_MASK_SHIFT) {
        set_oneshot_mods(one_shot_mods & ~MOD_MASK_SHIFT);
        is_shift = true;
    }

    if (is_paste) {
        if (is_shift) {
            SEND_STRING(SS_LSFT(SS_TAP(X_INSERT)));
        } else {
            SEND_STRING(SS_LCTRL("v"));
        }
    } else {
        if (is_shift) {
            SEND_STRING(SS_LCTRL(SS_TAP(X_INSERT)));
        } else {
            SEND_STRING(SS_LCTRL("c"));
        }
    }
}