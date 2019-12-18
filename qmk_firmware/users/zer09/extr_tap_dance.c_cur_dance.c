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
struct TYPE_3__ {int count; int /*<<< orphan*/  pressed; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int DEFAULT_HOLD ; 
 int DEFAULT_TAP ; 
 int DOUBLE_HOLD ; 
 int DOUBLE_TAP ; 
 int SINGLE_HOLD ; 
 int SINGLE_TAP ; 
 int TRIPLE_HOLD ; 
 int TRIPLE_TAP ; 

int cur_dance(qk_tap_dance_state_t *state) {
  switch (state->count) {
  case 1:
    return state->pressed == 0 ? SINGLE_TAP : SINGLE_HOLD;
  case 2:
    return state->pressed == 0 ? DOUBLE_TAP : DOUBLE_HOLD;
  case 3:
    return state->pressed == 0 ? TRIPLE_TAP : TRIPLE_HOLD;
  default:
    return state->pressed == 0 ? DEFAULT_TAP : DEFAULT_HOLD;
  }
}