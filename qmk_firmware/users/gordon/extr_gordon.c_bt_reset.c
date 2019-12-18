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
#define  DOUBLE_HOLD 132 
#define  DOUBLE_SINGLE_TAP 131 
#define  DOUBLE_TAP 130 
 int /*<<< orphan*/  KC_F3 ; 
 TYPE_1__ S1_state ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int _MACROS ; 
 int /*<<< orphan*/  layer_off (int) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void bt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (S1_state.state) {
    case SINGLE_TAP: unregister_code(KC_F3); break;
    case SINGLE_HOLD: layer_off(_MACROS); break;
    case DOUBLE_TAP: break; //already inverted. Don't do anything.
    case DOUBLE_HOLD: layer_off(5); break;
    case DOUBLE_SINGLE_TAP: break;
  }
  S1_state.state = 0;
}