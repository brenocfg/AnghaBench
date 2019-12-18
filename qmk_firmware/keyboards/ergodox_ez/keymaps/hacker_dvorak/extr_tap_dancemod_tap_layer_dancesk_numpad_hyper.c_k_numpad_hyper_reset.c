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
 int /*<<< orphan*/  KC_K ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  NUMPAD ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 TYPE_1__ k_numpad_hyper_state ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void k_numpad_hyper_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (k_numpad_hyper_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_K);
            break;

        case SINGLE_HOLD:
            layer_off(NUMPAD);
            break;

        case DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LGUI);
            break;
    }
    k_numpad_hyper_state.state = 0;
}