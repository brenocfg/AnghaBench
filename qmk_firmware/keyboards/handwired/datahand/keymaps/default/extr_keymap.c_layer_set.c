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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUNCTION_ARROWS ; 
 int /*<<< orphan*/  FUNCTION_MOUSE ; 
 int LED_FN ; 
 int LED_NAS ; 
 int LED_NORMAL ; 
 int LED_TENKEY ; 
 int /*<<< orphan*/  NAS ; 
 int /*<<< orphan*/  NAS_NUMLOCK ; 
 int /*<<< orphan*/  NAS_TENKEY ; 
 int /*<<< orphan*/  NAS_TENKEY_NUMLOCK ; 
 int /*<<< orphan*/  NORMAL ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 scalar_t__ layer_state_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_led_set (int) ; 
 scalar_t__ tenkey_enabled ; 

__attribute__((used)) static void layer_set(bool on, uint8_t layer) {
  if (on) {
    layer_on(layer);
  } else {
    layer_off(layer);
  }

  if (layer_state_is(NAS) || layer_state_is(NAS_NUMLOCK) || layer_state_is(NAS_TENKEY) || layer_state_is(NAS_TENKEY_NUMLOCK)) {
    if (tenkey_enabled) {
      mode_led_set(LED_NAS | LED_TENKEY);
    } else {
      mode_led_set(LED_NAS);
    }
  } else if (layer_state_is(FUNCTION_MOUSE) || layer_state_is(FUNCTION_ARROWS)) {
    mode_led_set(LED_FN);
  } else if (layer_state_is(NORMAL)) {
    mode_led_set(LED_NORMAL);
  }
}