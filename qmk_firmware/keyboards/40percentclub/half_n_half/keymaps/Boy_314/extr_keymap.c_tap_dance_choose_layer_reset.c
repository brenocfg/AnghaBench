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
 int /*<<< orphan*/  _DVORAK ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_state ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

void tap_dance_choose_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 1:
			layer_off(_LOWER);
			break;
		case 2:
			layer_off(_RAISE);
			break;
		case 3:
			if (biton32(default_layer_state) == _DVORAK) {
				set_single_persistent_default_layer(_QWERTY);
			}
			else if (biton32(default_layer_state) == _QWERTY) {
				set_single_persistent_default_layer(_DVORAK);
			}
			break;
	}
}