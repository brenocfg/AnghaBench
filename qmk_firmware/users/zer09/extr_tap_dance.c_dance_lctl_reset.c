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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLED ; 
 int /*<<< orphan*/  KC_LCTRL ; 
 size_t RBW_LCTL ; 
 TYPE_1__* rbw_led_keys ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void dance_lctl_reset(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_LCTRL);
  rbw_led_keys[RBW_LCTL].status = DISABLED;
}