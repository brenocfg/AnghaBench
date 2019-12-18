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
typedef  int /*<<< orphan*/  qk_tap_dance_state_t ;

/* Variables and functions */
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  _MACRO ; 
 int /*<<< orphan*/  _MOD ; 
 int cur_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int td_state ; 

void altlp_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      layer_on(_MACRO);
      break;
    case SINGLE_HOLD:
      layer_on(_MOD);
      break;
  }
}