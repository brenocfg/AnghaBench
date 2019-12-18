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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ _BL ; 
 scalar_t__ _GM ; 
 scalar_t__ active_layer ; 
 int gm_layer_act ; 
 int /*<<< orphan*/  layer_off (scalar_t__) ; 
 int /*<<< orphan*/  layer_on (scalar_t__) ; 

void layer_switcher_tap(uint8_t new_layer) {
  if (gm_layer_act == true) {
    layer_off(active_layer);
    if (new_layer == _BL) {
      layer_on(_GM);
      active_layer = _GM;
    } else {
      layer_on(new_layer);
      active_layer = new_layer;
    }
  } else {
    layer_off(active_layer);
    layer_on(new_layer);
    active_layer = new_layer;
  }
}