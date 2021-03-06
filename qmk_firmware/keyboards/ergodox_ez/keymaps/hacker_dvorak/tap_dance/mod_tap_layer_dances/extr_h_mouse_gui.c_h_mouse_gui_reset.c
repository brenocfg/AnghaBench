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
 int /*<<< orphan*/  KC_H ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  MOUSE ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 TYPE_1__ h_mouse_gui_state ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void h_mouse_gui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (h_mouse_gui_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_H);
            break;

        case SINGLE_HOLD:
            layer_off(MOUSE);
            break;

        case DOUBLE_HOLD:
            unregister_code(KC_LGUI);
            break;
    }
    h_mouse_gui_state.state = 0;
}