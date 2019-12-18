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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ALTER_LAYER ; 
#define  _COLEMA_LAYER 131 
 int /*<<< orphan*/  _COLEMA_LOWER_LAYER ; 
#define  _DVORAK_LAYER 130 
 int /*<<< orphan*/  _DVORAK_LOWER_LAYER ; 
#define  _QWERTY_LAYER 129 
 int /*<<< orphan*/  _QWERTY_LOWER_LAYER ; 
#define  _QWERTZ_LAYER 128 
 int /*<<< orphan*/  _QWERTZ_LOWER_LAYER ; 
 int /*<<< orphan*/  _RAISE_LAYER ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_state ; 
 int /*<<< orphan*/  update_tri_layer_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_user(uint32_t state) {
	switch (biton32(default_layer_state)) {
		case _QWERTY_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTY_LOWER_LAYER, _ALTER_LAYER);
			break;
		case _QWERTZ_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _QWERTZ_LOWER_LAYER, _ALTER_LAYER);
			break;
		case _COLEMA_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _COLEMA_LOWER_LAYER, _ALTER_LAYER);
			break;
		case _DVORAK_LAYER:
			state = update_tri_layer_state(state, _RAISE_LAYER, _DVORAK_LOWER_LAYER, _ALTER_LAYER);
			break;
	}
	return state;
}