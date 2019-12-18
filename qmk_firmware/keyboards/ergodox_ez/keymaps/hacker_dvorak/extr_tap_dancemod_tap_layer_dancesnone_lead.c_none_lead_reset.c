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
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_NO ; 
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 TYPE_1__ none_lead_state ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void none_lead_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (none_lead_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_NO);
            break;

        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            unregister_code(KC_LSFT);
            break;

        case DOUBLE_TAP:
            break;
    }
    none_lead_state.state = 0;
}