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
struct TYPE_3__ {int interrupted; int count; scalar_t__ pressed; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int DOUBLE_HOLD ; 
 int SINGLE_HOLD ; 
 int TRIPLE_HOLD ; 

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->interrupted == false || state->pressed) {
    if (state->count < 2) return SINGLE_HOLD;
    if (state->count < 3) return DOUBLE_HOLD;
    else return TRIPLE_HOLD;
  }
  else return 9;
}