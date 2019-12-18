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
typedef  int /*<<< orphan*/  qk_tap_dance_state_t ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARROWS ; 
#define  DOUBLE_HOLD 130 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_U ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int current_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 TYPE_1__ u_arrows_gui_state ; 

void u_arrows_gui_finished(qk_tap_dance_state_t *state, void *user_data) {
    u_arrows_gui_state.state = current_dance(state);
    switch (u_arrows_gui_state.state) {
        case SINGLE_TAP:
            register_code(KC_U);
            break;

        case SINGLE_HOLD:
            layer_on(ARROWS);
            break;

        case DOUBLE_HOLD:
            register_code(KC_LGUI);
            break;
    }
}