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
#define  DOUBLE_HOLD 131 
#define  DOUBLE_TAP 130 
 int /*<<< orphan*/  KC_AT ; 
 int /*<<< orphan*/  ONESHOT_START ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  _FUNCTION ; 
 int /*<<< orphan*/  _UPPER ; 
 int cur_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_code16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  set_oneshot_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ xtap_state ; 

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
	xtap_state.state = cur_dance(state);
	switch (xtap_state.state) {
		case SINGLE_TAP: register_code16(KC_AT); break;
		case SINGLE_HOLD: set_oneshot_layer(_UPPER, ONESHOT_START); break;
		case DOUBLE_TAP: set_oneshot_layer(_FUNCTION, ONESHOT_START); break;
		case DOUBLE_HOLD: reset_keyboard(); break;
	}
}