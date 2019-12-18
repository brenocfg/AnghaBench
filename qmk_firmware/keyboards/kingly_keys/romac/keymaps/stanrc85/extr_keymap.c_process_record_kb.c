#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
typedef  int /*<<< orphan*/  keypos_t ;

/* Variables and functions */
#define  D_LAYR 129 
#define  U_LAYR 128 
 int /*<<< orphan*/  layer_move (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_switch_get_layer (int /*<<< orphan*/ ) ; 

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  keypos_t key;
  uint8_t current_layer;
  uint8_t next_layer;
  switch (keycode) {
  case U_LAYR: //cycles up the layers
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer+1;
      layer_move(next_layer);
    }
    break;
  case D_LAYR: //cycles down the layers
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer-1;
      layer_move(next_layer);
    }
    break;
  }
  return true;
}