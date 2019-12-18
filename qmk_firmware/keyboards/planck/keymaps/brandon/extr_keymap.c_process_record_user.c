#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int nkro; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 unsigned long BASE_COLEMAK_LAYER ; 
 unsigned long BASE_QWERTY_LAYER ; 
 int /*<<< orphan*/  BASE_STENO_LAYER ; 
#define  COLEMAK 134 
 int /*<<< orphan*/  KEYBOARD_LAYER ; 
#define  LOWER 133 
 int /*<<< orphan*/  LOWER_LAYER ; 
#define  PV_EXIT 132 
#define  PV_LOOK 131 
#define  QWERTY 130 
#define  RAISE 129 
 int /*<<< orphan*/  RAISE_LAYER ; 
#define  STENO 128 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_keymap () ; 
 int /*<<< orphan*/  eeconfig_update_keymap (int /*<<< orphan*/ ) ; 
 TYPE_4__ keymap_config ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistant_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  plover_lookup () ; 
 int /*<<< orphan*/  plover_resume () ; 
 int /*<<< orphan*/  plover_suspend () ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<BASE_QWERTY_LAYER);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<BASE_COLEMAK_LAYER);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(LOWER_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      } else {
        layer_off(LOWER_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(RAISE_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      } else {
        layer_off(RAISE_LAYER);
        update_tri_layer(LOWER_LAYER, RAISE_LAYER, KEYBOARD_LAYER);
      }
      return false;
    case STENO:
      if (record->event.pressed) {
        layer_off(RAISE_LAYER);
        layer_off(LOWER_LAYER);
        layer_off(KEYBOARD_LAYER);
        layer_on(BASE_STENO_LAYER);
        if (!eeconfig_is_enabled()) {
          eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
        plover_resume();
      }
      return false;
    case PV_EXIT:
      if (record->event.pressed) {
        plover_suspend();
        layer_off(BASE_STENO_LAYER);
      }
      return false;
    case PV_LOOK:
      if (record->event.pressed) {
        plover_lookup();
      }
      return false;
  }
  return true;
}