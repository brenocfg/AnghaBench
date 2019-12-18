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
typedef  int uint32_t ;

/* Variables and functions */
 int NUM ; 
 int /*<<< orphan*/  set_led_to ; 
 int /*<<< orphan*/  set_numpad_colours (int,int /*<<< orphan*/ *) ; 

uint32_t layer_state_set_user(uint32_t state) {
  if (state & (1<<NUM)) {
    set_numpad_colours(1, &set_led_to);
  } else {
    set_numpad_colours(0, &set_led_to);
  }

  return state;
}