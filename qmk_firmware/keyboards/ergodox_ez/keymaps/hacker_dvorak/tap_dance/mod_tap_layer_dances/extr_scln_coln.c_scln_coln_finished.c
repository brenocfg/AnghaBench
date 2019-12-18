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
#define  DOUBLE_TAP 130 
 int /*<<< orphan*/  KC_COLN ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_SCLN ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int current_dance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code16 (int /*<<< orphan*/ ) ; 
 TYPE_1__ scln_coln_state ; 

void scln_coln_finished(qk_tap_dance_state_t *state, void *user_data) {
    scln_coln_state.state = current_dance(state);
    switch (scln_coln_state.state) {
        case SINGLE_TAP:
            register_code(KC_SCLN);
            break;

        case SINGLE_HOLD:
            register_code(KC_LALT);
            register_code(KC_LSFT);
            register_code(KC_LGUI);
            break;

        case DOUBLE_TAP:
            register_code16(KC_COLN);
            break;
    }
}