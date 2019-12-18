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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
#define  _CMD 128 
 int biton32 (scalar_t__) ; 
 int /*<<< orphan*/  user_led_off () ; 
 int /*<<< orphan*/  user_led_on () ; 

uint32_t layer_state_set_user(uint32_t state) {
  static uint32_t last_state = 0;

  if(last_state != state) {
    switch (biton32(state)) {
    case _CMD:
      user_led_on();
      break;
    default:
      user_led_off();
      break;
    }
    last_state = state;
  }
  return state;
}