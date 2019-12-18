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
 int /*<<< orphan*/  KC_CAPS ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_NLCK ; 
 int /*<<< orphan*/  KC_SLCK ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void dance_lock_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 1: unregister_code(KC_LGUI); break;
		case 2: unregister_code(KC_NLCK); break;
		case 3: register_code(KC_CAPS); break;
		case 4: register_code(KC_SLCK); break;
		default: break;
	}
}