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
#define  DUAL 133 
#define  DVORAK 132 
#define  GAME 131 
#define  LEFTY 130 
#define  QWERTY 129 
#define  RIGHTY 128 
 int /*<<< orphan*/  _DUAL ; 
 unsigned long _DVORAK ; 
 unsigned long _GAME ; 
 int /*<<< orphan*/  _LEFTY ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  _RIGHTY ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_GAME);
      }
      return false;
      break;
    case LEFTY:
      if (record->event.pressed) {
        layer_on(_LEFTY);
        update_tri_layer(_LEFTY, _RIGHTY, _DUAL);
      } else {
        layer_off(_LEFTY);
        update_tri_layer(_LEFTY, _RIGHTY, _DUAL);
      }
      return false;
      break;
    case RIGHTY:
      if (record->event.pressed) {
        layer_on(_RIGHTY);
        update_tri_layer(_LEFTY, _RIGHTY, _DUAL);
      } else {
        layer_off(_RIGHTY);
        update_tri_layer(_LEFTY, _RIGHTY, _DUAL);
      }
      return false;
      break;
    case DUAL:
      if (record->event.pressed) {
        layer_on(_DUAL);
      } else {
        layer_off(_DUAL);
      }
      return false;
      break;
  }
  return true;
}