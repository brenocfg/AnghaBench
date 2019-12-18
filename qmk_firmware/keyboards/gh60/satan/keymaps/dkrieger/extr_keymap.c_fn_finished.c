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
#define  DOUBLE_HOLD 130 
#define  SINGLE_HOLD 129 
#define  TRIPLE_HOLD 128 
 int /*<<< orphan*/  _FN ; 
 int /*<<< orphan*/  _MOUSE ; 
 int /*<<< orphan*/  _UTIL ; 
 int cur_dance (int /*<<< orphan*/ *) ; 
 TYPE_1__ fn_tap_state ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 

void fn_finished (qk_tap_dance_state_t *state, void *user_data) {
  fn_tap_state.state = cur_dance(state);
  switch (fn_tap_state.state) {
    /* case SINGLE_HOLD: register_code(MO(_FN)); break; */
    case SINGLE_HOLD: layer_on(_FN); break;
    case DOUBLE_HOLD: layer_on(_MOUSE); break;
    case TRIPLE_HOLD: layer_on(_UTIL);
  }
}