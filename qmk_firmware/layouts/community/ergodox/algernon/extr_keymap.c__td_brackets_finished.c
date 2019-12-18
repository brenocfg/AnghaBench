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
struct TYPE_3__ {int count; scalar_t__ keycode; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CT_LBP ; 
 int /*<<< orphan*/  KC_LBRC ; 
 int /*<<< orphan*/  KC_LPRN ; 
 int /*<<< orphan*/  KC_RBRC ; 
 int /*<<< orphan*/  KC_RPRN ; 
 scalar_t__ TD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_hex (int) ; 
 int /*<<< orphan*/  unicode_input_finish () ; 
 int /*<<< orphan*/  unicode_input_start () ; 

__attribute__((used)) static void
_td_brackets_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->keycode == TD(CT_LBP))
      register_code16 (KC_LBRC);
    else
      register_code16 (KC_RBRC);
  } else if (state->count == 2) {
    if (state->keycode == TD(CT_LBP))
      register_code16 (KC_LPRN);
    else
      register_code16 (KC_RPRN);
  } else if (state->count == 3) {
    unicode_input_start();

    if (state->keycode == TD(CT_LBP))
      register_hex (0x300c);
    else
      register_hex (0x300d);

    unicode_input_finish();
  }
}