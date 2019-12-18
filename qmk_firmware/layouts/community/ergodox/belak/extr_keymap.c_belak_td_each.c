#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 
 int td_led_override ; 

void belak_td_each(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
    case 1:
        td_led_override = 1;
        break;
    case 2:
        td_led_override = 2;
        break;
    default:
        reset_tap_dance(state);
    }
}