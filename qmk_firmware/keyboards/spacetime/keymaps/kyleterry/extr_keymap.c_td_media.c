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
 int /*<<< orphan*/  KC_MPLY ; 
 int /*<<< orphan*/  KC_MUTE ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 

void td_media(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16(KC_MPLY);
      reset_tap_dance(state);
      break;
    case 2:
      tap_code16(KC_MUTE);
      reset_tap_dance(state);
      break;
  }
}