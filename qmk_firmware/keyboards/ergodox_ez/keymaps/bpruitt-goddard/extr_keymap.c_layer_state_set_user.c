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
 scalar_t__ LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC ; 
 int /*<<< orphan*/  NUM ; 
 int /*<<< orphan*/  QWERTY ; 
 int /*<<< orphan*/  current_layer_state ; 
 scalar_t__ is_macro1_recording ; 
 int /*<<< orphan*/  led_1_off () ; 
 int /*<<< orphan*/  led_1_on () ; 
 int /*<<< orphan*/  led_2_off () ; 
 int /*<<< orphan*/  led_2_on () ; 
 int /*<<< orphan*/  led_3_off () ; 
 int /*<<< orphan*/  led_3_on () ; 

uint32_t layer_state_set_user(uint32_t state) {
  current_layer_state = state;

  if (is_macro1_recording) {
    led_1_on();
    led_2_on();
    led_3_on();
    return state;
  }

  if (LAYER_ON(NUM)) {
    led_1_on();
  } else {
    led_1_off();
  }

  if (LAYER_ON(MAC)) {
    led_2_on();
  } else {
    led_2_off();
  }

  if (LAYER_ON(QWERTY)) {
    led_3_on();
  } else {
    led_3_off();
  }

  return state;
}