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
struct TYPE_2__ {int semicolon; } ;

/* Variables and functions */
#define  DOUBLE_HOLD 130 
 int /*<<< orphan*/  KC_SCLN ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  _NUM ; 
 int hold_cur_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 TYPE_1__ tap_state ; 

void tap_dance_semicolon_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.semicolon = hold_cur_dance(state);
  switch (tap_state.semicolon) {
    case SINGLE_TAP: case DOUBLE_HOLD: register_code(KC_SCLN); break;
    case SINGLE_HOLD: layer_on(_NUM); break;
  }
}