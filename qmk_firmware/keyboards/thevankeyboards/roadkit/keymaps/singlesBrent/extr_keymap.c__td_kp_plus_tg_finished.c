#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_KP_PLUS ; 
 int /*<<< orphan*/  _L1 ; 
 int /*<<< orphan*/  _L2 ; 
 int /*<<< orphan*/  _L3 ; 
 int /*<<< orphan*/  backlight_set (int) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 

void _td_kp_plus_tg_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_KP_PLUS);
  } else if (state->count == 2) {
//    layer_invert(_L1);
    backlight_set(2);
	layer_on(_L1);
	layer_off(_L2);
	layer_off(_L3);
  }
}