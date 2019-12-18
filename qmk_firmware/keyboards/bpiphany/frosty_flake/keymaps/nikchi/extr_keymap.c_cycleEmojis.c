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
 size_t EMOTIS ; 
 int /*<<< orphan*/  KC_BSPC ; 
 scalar_t__ pgm_read_dword (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_hex32 (scalar_t__) ; 
 int /*<<< orphan*/  tap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unicode_input_finish () ; 
 int /*<<< orphan*/  unicode_input_start () ; 
 int /*<<< orphan*/ * unicode_map ; 

void cycleEmojis(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[EMOTIS]));
    unicode_input_finish();
  }
  else if(state->count <= 80) {
    tap(KC_BSPC);
    unicode_input_start();
    register_hex32(pgm_read_dword(&unicode_map[EMOTIS])+state->count);
    unicode_input_finish();
  }
}