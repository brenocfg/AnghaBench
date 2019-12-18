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
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 
 int /*<<< orphan*/  send_unicode_hex_string (char*) ; 

void dance_key_two (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        send_unicode_hex_string("0CA0 005F 0CA0"); // ಠ_ಠ
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 2) {
        send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B"); // (ノಠ痊ಠ)ノ彡┻━┻
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 3) {
        send_unicode_hex_string("256D 2229 256E 0028 002D 005F 002D 0029 256D 2229 256E"); // ╭∩╮(-_-)╭∩╮
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 4) {
        send_unicode_hex_string("0028 3065 FFE3 0020 00B3 FFE3 0029 3065"); // (づ￣ ³￣)づ
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    } else if (state->count == 5) {
        send_unicode_hex_string("0028 FE3A FE39 FE3A 0029"); // (︺︹︺)
        SEND_STRING(SS_TAP(X_ENTER));
        reset_tap_dance (state);
    }
}