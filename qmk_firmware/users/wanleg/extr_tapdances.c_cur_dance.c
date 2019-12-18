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
 int DOUBLE_HOLD ; 
 int DOUBLE_SINGLE_TAP ; 
 int DOUBLE_TAP ; 
 int SINGLE_HOLD ; 
 int SINGLE_TAP ; 
 int TRIPLE_HOLD ; 
 int TRIPLE_SINGLE_TAP ; 
 int TRIPLE_TAP ; 

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    if (state->interrupted) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }

  //If count = 3, and it has been interrupted - assume that user is trying to type the letter associated
  //with double tap.
  else if (state->count == 3) {
    if (state->interrupted) return TRIPLE_SINGLE_TAP;
    else if (state->pressed) return TRIPLE_HOLD;
    else return TRIPLE_TAP;
  }
  else return 9; //magic number. At some point this method will expand to work for more presses
}