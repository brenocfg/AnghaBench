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
 int /*<<< orphan*/  LAYERS ; 
 int /*<<< orphan*/  MDIA ; 
 int /*<<< orphan*/  SYMB ; 
 int /*<<< orphan*/  SYMB_ON_BEPO ; 
 int /*<<< orphan*/  layer_invert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_qwerty () ; 
 int /*<<< orphan*/  reset_tap_dance (TYPE_1__*) ; 

void tap_dance_layer_switch (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count){
  case 1:
    if(on_qwerty())
      layer_invert(SYMB);
    else
         layer_invert(SYMB_ON_BEPO);
    break;
  case 2:
    layer_invert(MDIA);
    break;
  case 3:
    layer_invert(LAYERS);
  default:
    break;
  }
  reset_tap_dance(state);
}