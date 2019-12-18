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
#define  DOUBLE_HOLD 133 
#define  DOUBLE_TAP 132 
 int /*<<< orphan*/  KC_CALCULATOR ; 
 int /*<<< orphan*/  KC_COMMA ; 
#define  SINGLE_HOLD 131 
#define  SINGLE_TAP 130 
#define  TRIPLE_HOLD 129 
#define  TRIPLE_TAP 128 
 TYPE_1__ comma_state ; 
 int hold_cur_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layer_invert (int) ; 
 int /*<<< orphan*/  layer_on (int) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 

void comma_finished (qk_tap_dance_state_t *state, void *user_data) {
  comma_state.state = hold_cur_dance(state); //Use the dance that favors being held
  switch (comma_state.state) {
    case SINGLE_TAP: register_code(KC_COMMA); break;
    case SINGLE_HOLD: layer_on(1); break; //turn on symbols layer
    case DOUBLE_TAP: layer_invert(4); break; //toggle numbers layer
    case DOUBLE_HOLD: layer_on(2); break;
    case TRIPLE_TAP: register_code(KC_CALCULATOR); break;
    case TRIPLE_HOLD: layer_on(3);
  }
}