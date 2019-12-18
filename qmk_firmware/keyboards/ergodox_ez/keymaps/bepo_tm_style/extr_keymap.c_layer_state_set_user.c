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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FN ; 
 scalar_t__ LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOUSE ; 
 int /*<<< orphan*/  NUMS ; 
 int /*<<< orphan*/  SWAP ; 
 int /*<<< orphan*/  SYSLEDS ; 
 int /*<<< orphan*/  current_layer_state ; 
 scalar_t__ is_macro1_recording ; 
 int /*<<< orphan*/  led_1_off () ; 
 int /*<<< orphan*/  led_1_on () ; 
 int /*<<< orphan*/  led_2_off () ; 
 int /*<<< orphan*/  led_2_on () ; 
 int /*<<< orphan*/  led_3_off () ; 
 int /*<<< orphan*/  led_3_on () ; 
 int /*<<< orphan*/  led_set_user (int /*<<< orphan*/ ) ; 
 scalar_t__ swap_hands ; 
 int /*<<< orphan*/  sys_led_state ; 

uint32_t layer_state_set_user(uint32_t state) {
  current_layer_state = state;
  swap_hands = LAYER_ON(SWAP);

  if (is_macro1_recording) {
    led_1_on();
    led_2_on();
    led_3_on();
    return state;
  }

  if (LAYER_ON(SYSLEDS)) {
    led_set_user(sys_led_state);
    return state;
  }

  if (LAYER_ON(FN)) {
    led_1_on();
  } else {
    led_1_off();
  }

  if (LAYER_ON(NUMS)) {
    led_2_on();
  } else {
    led_2_off();
  }

  if (LAYER_ON(MOUSE)) {
    led_3_on();
  } else {
    led_3_off();
  }

  return state;
}