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
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_NONUS_BSLASH ; 
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 

void cmd_sft_slash_pipe_down (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || state->pressed==0) {
      register_code (KC_NONUS_BSLASH);
    } else {
      register_code (KC_LSFT);
    }
  } else if (state->count == 2) {
    register_mods(MOD_BIT(KC_LSFT));
    register_code(KC_NONUS_BSLASH);
  }
}