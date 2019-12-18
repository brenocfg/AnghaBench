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
struct TYPE_3__ {int count; scalar_t__ pressed; scalar_t__ interrupted; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int DOUBLE_HOLD ; 
 int DOUBLE_SINGLE_TAP ; 
 int DOUBLE_TAP ; 
 int SINGLE_HOLD ; 
 int SINGLE_TAP ; 
 int TRIPLE_HOLD ; 
 int TRIPLE_SINGLE_TAP ; 
 int TRIPLE_TAP ; 

int current_dance(qk_tap_dance_state_t *state) {
    int current_state = 0;
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            current_state = SINGLE_TAP;
        } else {
            current_state = SINGLE_HOLD; //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        }
    } else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
        */
        if (state->interrupted) {
            current_state = DOUBLE_SINGLE_TAP;
        } else if (state->pressed) {
            current_state = DOUBLE_HOLD;
        } else {
            current_state = DOUBLE_TAP;
        }
    } else if (state->count == 3) {
        if (state->interrupted) {
            current_state = TRIPLE_SINGLE_TAP;
        } else if (state->pressed) {
            current_state = TRIPLE_HOLD;
        } else {
            current_state = TRIPLE_TAP;
        }
    }
    return current_state;
}