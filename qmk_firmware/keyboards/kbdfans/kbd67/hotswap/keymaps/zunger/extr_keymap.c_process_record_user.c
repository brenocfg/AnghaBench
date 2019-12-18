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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 scalar_t__ KC_LSHIFT ; 
 scalar_t__ KC_RSHIFT ; 
 int LAYER_MASK ; 
 scalar_t__ MAGIC ; 
 int MAGIC_LAYER ; 
 scalar_t__ RESET ; 
 int SHIFTMAGIC_LAYER ; 
 int layer_state ; 
 int /*<<< orphan*/  layer_state_set (int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Activate the appropriate magic layer:
  //   User is holding AltGr+Shift => _SHIFTMAGIC
  //   User is holding AltGr       => _MAGIC
  //   Not holding AltGr           => None
  // We do this the efficient way, by grabbing the non-magic bits from the current layer bitmap,
  // setting the appropriate magic or shiftmagic bit, and doing an absolute layer set. (Layer
  // sets are nontrivial, so we don't want to do extras!)

  // We track shift and AltGr state on our own, because this function is called before get_mods is
  // updated!
  static bool shifted = false;
  static bool magic = false;

  if (keycode == KC_LSHIFT || keycode == KC_RSHIFT) {
    shifted = record->event.pressed;
  } else if (keycode == MAGIC) {
    magic = record->event.pressed;
  } else if (keycode == RESET) {
    // Safe reset: Only actually let this keycode through if shift is held as well. Since there's no
    // right-shift in the function layer, this means that reset is Fn+LShift+Esc, something you're
    // not likely to hit by accident. (Especially since AltGr+Esc is backtick!)
    return (record->event.pressed && shifted);
  }

  // Update the layer.
  uint32_t new_layer_state = layer_state & LAYER_MASK;
  if (magic) {
    new_layer_state |= (shifted ? SHIFTMAGIC_LAYER : MAGIC_LAYER);
  }
  if (layer_state != new_layer_state) {
    layer_state_set(new_layer_state);
  }

  return true;
}