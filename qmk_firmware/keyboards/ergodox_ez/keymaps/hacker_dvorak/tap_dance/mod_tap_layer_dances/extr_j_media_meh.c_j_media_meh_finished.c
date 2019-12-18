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
 int /*<<< orphan*/  KC_J ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  MEDIA_FN ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int current_dance (int /*<<< orphan*/ *) ; 
 TYPE_1__ j_media_meh_state ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 

void j_media_meh_finished(qk_tap_dance_state_t *state, void *user_data) {
    j_media_meh_state.state = current_dance(state);
    switch (j_media_meh_state.state) {
        case SINGLE_TAP:
            register_code(KC_J);
            break;

        case SINGLE_HOLD:
            layer_on(MEDIA_FN);
            break;

        case DOUBLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_LALT);
            break;
    }
}