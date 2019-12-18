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
struct TYPE_2__ {int raise; } ;

/* Variables and functions */
#define  DOUBLE_TAP 130 
#define  HOLD 129 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  _RAISE ; 
 int cur_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_japanese_mode (int) ; 
 TYPE_1__ td_status ; 

void td_raise_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_status.raise = cur_dance(state);
  switch(td_status.raise) {
    case DOUBLE_TAP:
      // same as single
    case SINGLE_TAP:
      set_japanese_mode(true);
      break;
    case HOLD:
      break;
  }
  layer_on(_RAISE);
}