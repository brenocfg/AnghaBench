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
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int layer_state_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int) ; 
 int /*<<< orphan*/  unregister_code (int) ; 

void press_without(int pressed, int key, uint8_t layer)
{
  static bool was_on;
  if (pressed) {
    was_on = layer_state_is(layer);
    layer_off(layer);
    register_code(key);
  } else {
    if (was_on) layer_on(layer);
    unregister_code(key);
  }
}