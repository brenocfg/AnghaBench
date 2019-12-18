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
#define  DOUBLE_HOLD 134 
#define  DOUBLE_SINGLE_TAP 133 
#define  DOUBLE_TAP 132 
#define  SINGLE_HOLD 131 
#define  SINGLE_TAP 130 
#define  TRIPLE_HOLD 129 
#define  TRIPLE_TAP 128 
 int /*<<< orphan*/  _FUNCTION ; 
 int /*<<< orphan*/  _MOUSE ; 
 int /*<<< orphan*/  _NUMPAD ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 TYPE_1__ ttt_state ; 

void TTT_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ttt_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_off(_FUNCTION); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: layer_off(_NUMPAD); break;
    case DOUBLE_SINGLE_TAP:  break;
    case TRIPLE_TAP:  break;
    case TRIPLE_HOLD: layer_off(_MOUSE); break;
  }
  ttt_state.state = 0;
}