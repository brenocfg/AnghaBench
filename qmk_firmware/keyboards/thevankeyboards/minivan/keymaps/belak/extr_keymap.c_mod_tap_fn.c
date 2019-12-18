#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; size_t keycode; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
 size_t QK_TAP_DANCE ; 
 int /*<<< orphan*/  _L1 ; 
 int /*<<< orphan*/  _L2 ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 
 int /*<<< orphan*/  send_keyboard_report () ; 
 int /*<<< orphan*/ * tap_dance_keys ; 

void mod_tap_fn(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            register_mods(MOD_BIT(tap_dance_keys[state->keycode - QK_TAP_DANCE]));
            send_keyboard_report();
            break;
        case 2:
            layer_on(_L2);
            break;
        case 3:
            layer_off(_L2);
            layer_on(_L1);
            break;
        default:
            reset_tap_dance(state);
    }
}