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
struct TYPE_2__ {scalar_t__ lower; } ;

/* Variables and functions */
 scalar_t__ DOUBLE_TAP ; 
 int /*<<< orphan*/  KC_ESC ; 
 scalar_t__ NONE ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 TYPE_1__ td_status ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void td_lower_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (td_status.lower == DOUBLE_TAP) {
    unregister_code(KC_ESC);
  }
  layer_off(_LOWER);
  td_status.lower = NONE;
}