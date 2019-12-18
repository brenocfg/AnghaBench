#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDIA ; 
 int /*<<< orphan*/  RIMW ; 
 int /*<<< orphan*/  SYMB ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 

void cake_count (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_on (SYMB);        //define double tap here
    layer_off (MDIA);
  } 
  else {    
    layer_off (SYMB);       //define single tap or hold here
    layer_off (MDIA);
  }
  if (state->count == 3) {         
     layer_on (RIMW);       //define triple tap here
     layer_off (MDIA);
  } 
  else {    
   	layer_off (RIMW);       //define single tap or hold here
	layer_off (MDIA);
    reset_tap_dance (state);
  }
}