#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  B0 ; 
 int GET_FLASH_PERIOD ; 
 scalar_t__ IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAYER_SWITCH ; 
 int TIMEOUT_WARNING ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int layer_time_remaining ; 
 scalar_t__ prev_loop_time ; 
 scalar_t__ timer_read () ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void matrix_scan_user(void) {
  layer_time_remaining -= timer_read()-prev_loop_time; //amount of time elapsed since the start of the previous loop
  prev_loop_time = timer_read(); //start counting the time to check at the next iteration

  if (layer_time_remaining <= 0) {
  	// once timer run out
  	layer_off(LAYER_SWITCH);
  }

  // escape LED on layer 1
  if (IS_LAYER_ON(LAYER_SWITCH)) {
    if (layer_time_remaining <= TIMEOUT_WARNING) {
      if ((int)(layer_time_remaining/GET_FLASH_PERIOD % 2 == 0)) {
		    // if even led on
		    writePinLow(B0);
		  } else {
		    writePinHigh(B0);
		  }
    } else {
      writePinLow(B0);
    }
  } else {
    writePinHigh(B0);
  }
}