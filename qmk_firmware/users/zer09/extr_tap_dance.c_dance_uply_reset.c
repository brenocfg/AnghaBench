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
struct TYPE_2__ {int state; } ;

/* Variables and functions */
#define  SINGLE_HOLD 129 
#define  SINGLE_TAP 128 
 int /*<<< orphan*/  _BL ; 
 int /*<<< orphan*/  layer_switcher_tap (int /*<<< orphan*/ ) ; 
 TYPE_1__ upltap_state ; 

void dance_uply_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (upltap_state.state) {
  case SINGLE_TAP:
    break;
  case SINGLE_HOLD:
  default:
    layer_switcher_tap(_BL);
    break;
  }
  upltap_state.state = 0;
}