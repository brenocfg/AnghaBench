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
struct TYPE_3__ {int count; int /*<<< orphan*/  pressed; int /*<<< orphan*/  interrupted; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int DOUBLE_TAP ; 
 int SINGLE_HOLD ; 
 int SINGLE_TAP ; 
 int TRIPLE_TAP ; 

int cur_dance(qk_tap_dance_state_t *state) {
  int press = 0;
  switch(state->count) {
    case 1:
      press = (state->interrupted || !state->pressed)
        ? SINGLE_TAP
        : SINGLE_HOLD;
      break;
     case 2:
      press = DOUBLE_TAP;
      break;
    case 3:
      press = TRIPLE_TAP;
  }
  return press;
}