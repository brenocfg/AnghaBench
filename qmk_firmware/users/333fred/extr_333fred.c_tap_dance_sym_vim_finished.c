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
struct TYPE_3__ {int count; scalar_t__ pressed; scalar_t__ interrupted; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
#define  DOUBLE 130 
 int /*<<< orphan*/  ONESHOT_START ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  SYMB ; 
 int /*<<< orphan*/  VIM ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_oneshot_layer () ; 
 int /*<<< orphan*/  set_oneshot_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tap_dance_active ; 
 int tap_dance_state ; 

void tap_dance_sym_vim_finished(qk_tap_dance_state_t *state, void *user_data) {
    // Determine the current state
    if (state->count == 1) {
        if (state->interrupted || state->pressed == 0) tap_dance_state = SINGLE_TAP;
        else tap_dance_state = SINGLE_HOLD;
    } else {
        // Handle any number of other taps as a VIM movement hold
        tap_dance_state = DOUBLE;
    }

    switch (tap_dance_state) {
        case SINGLE_TAP:
            if (tap_dance_active) {
                reset_oneshot_layer();
                tap_dance_active = false;
            } else {
                set_oneshot_layer(SYMB, ONESHOT_START);
                tap_dance_active = true;
            }
            break;
        case SINGLE_HOLD:
            layer_on(SYMB);
            break;
        case DOUBLE:
            layer_on(VIM);
            break;
    }
}