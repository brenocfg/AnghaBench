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
 TYPE_1__ BSWtap_state ; 
#define  DOUBLE_TAP 129 
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_ENTER ; 
 int /*<<< orphan*/  KC_LCTRL ; 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void BSW_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (BSWtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_ENTER); break;
    case DOUBLE_TAP:
	  unregister_code(KC_LCTRL);
	  unregister_code(KC_C);
	  break;
  }
  BSWtap_state.state = 0;
}