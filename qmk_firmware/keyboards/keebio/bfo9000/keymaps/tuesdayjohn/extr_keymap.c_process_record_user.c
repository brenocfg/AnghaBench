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
struct TYPE_7__ {int nkro; } ;

/* Variables and functions */
#define  COLEMAK 130 
#define  GAMING 129 
#define  QWERTY 128 
 unsigned long _COLEMAK ; 
 int /*<<< orphan*/  _GAMING ; 
 int /*<<< orphan*/  _NUMPAD ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  default_layer_set (unsigned long) ; 
 TYPE_4__ keymap_config ; 
 int /*<<< orphan*/  layer_invert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_move (unsigned long) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	case COLEMAK:
      if (record->event.pressed) {
//        persistent_default_layer_set(1UL << _COLEMAK);
        default_layer_set(1UL << _COLEMAK);
        layer_move (_COLEMAK);
        keymap_config.nkro = 0;
	  }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
//        persistent_default_layer_set(1UL << _QWERTY);
        default_layer_set(1UL << _QWERTY);
        layer_move (_QWERTY);
        keymap_config.nkro = 0;
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        layer_invert (_GAMING);
        layer_off (_NUMPAD);
        keymap_config.nkro = 1;
	  }
      return false;
      break;
  }
  return true;
}