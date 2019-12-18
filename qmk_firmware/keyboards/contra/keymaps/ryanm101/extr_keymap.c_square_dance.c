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
struct TYPE_3__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LEFT ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void square_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("[]"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("[");
  } else if (state->count == 3) {
    SEND_STRING("]");
  }
}