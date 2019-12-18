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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  COLEMAK 129 
#define  QWERTY 128 
 unsigned long _ADJUST ; 
 unsigned long _ADJUST2 ; 
 unsigned long _COLEMAK ; 
 unsigned long _FUNCTION ; 
 unsigned long _FUNCTION2 ; 
 unsigned long _NUMBERS ; 
 unsigned long _NUMBERS2 ; 
 unsigned long _NUMPAD ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  layer_off (unsigned long) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        default_layer_set(1UL << _COLEMAK);
        layer_off ( _QWERTY);
        layer_off ( _NUMBERS);
        layer_off ( _NUMBERS2);
        layer_off ( _FUNCTION);
        layer_off ( _FUNCTION2);
        layer_off ( _NUMPAD);
        layer_off ( _ADJUST);
		layer_off ( _ADJUST2);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        default_layer_set(1UL << _QWERTY);
        layer_off ( _COLEMAK);
        layer_off ( _NUMBERS);
        layer_off ( _NUMBERS2);
        layer_off ( _FUNCTION);
        layer_off ( _FUNCTION2);
        layer_off ( _NUMPAD);
        layer_off ( _ADJUST);
		layer_off ( _ADJUST2);
      }
      return false;
      break;
  }
  return true;
}