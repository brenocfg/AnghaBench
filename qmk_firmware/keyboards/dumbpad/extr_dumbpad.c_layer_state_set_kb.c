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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  LAYER_INDICATOR_LED_0 ; 
 int /*<<< orphan*/  LAYER_INDICATOR_LED_1 ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state_set_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePin (int /*<<< orphan*/ ,int) ; 

layer_state_t layer_state_set_kb(layer_state_t state) {
  // Layer LEDs act as binary indication of current layer
  uint8_t layer = biton32(state);
  writePin(LAYER_INDICATOR_LED_0, layer & 0b1);
  writePin(LAYER_INDICATOR_LED_1, (layer >> 1) & 0b1);
  return layer_state_set_user(state);
}