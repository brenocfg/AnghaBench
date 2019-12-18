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
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_ENTER ; 
 int /*<<< orphan*/  cycle_unicode_input_mode (int) ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 
 int /*<<< orphan*/  send_unicode_hex_string (char*) ; 

void dance_key_one (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF"); // ¯\_(ツ)_/¯
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 2) {
        cycle_unicode_input_mode(+1);
        reset_tap_dance (state);
    }
}