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
#define  DOUBLE_HOLD 131 
#define  SINGLE_HOLD 130 
#define  SINGLE_TAP 129 
#define  TRIPLE_TAP 128 
 int /*<<< orphan*/  _BL ; 
 TYPE_1__ dwltap_state ; 
 int /*<<< orphan*/  layer_switcher_tap (int /*<<< orphan*/ ) ; 

void dance_dwly_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (dwltap_state.state) {
  case SINGLE_TAP:
    break;
  case SINGLE_HOLD:
  case DOUBLE_HOLD:
  case TRIPLE_TAP:
  default:
    layer_switcher_tap(_BL);
    break;
  }
  dwltap_state.state = 0;
}