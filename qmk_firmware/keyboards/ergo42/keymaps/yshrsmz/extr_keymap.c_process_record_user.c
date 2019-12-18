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
#define  BASE 133 
#define  EISU 132 
#define  GAME 131 
#define  KANA 130 
 int /*<<< orphan*/  KC_LANG1 ; 
 int /*<<< orphan*/  KC_LANG2 ; 
#define  META 129 
#define  SYMB 128 
 unsigned long _BASE ; 
 int /*<<< orphan*/  _GAME ; 
 int /*<<< orphan*/  _META ; 
 int /*<<< orphan*/  _SYMB ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_BASE);
      }
      return false;
      break;
    case META:
      if (record->event.pressed) {
        layer_on(_META);
        update_tri_layer(_META, _SYMB, _GAME);
      } else {
        layer_off(_META);
        update_tri_layer(_META, _SYMB, _GAME);
      }
      return false;
      break;
    case SYMB:
      if (record->event.pressed) {
        layer_on(_SYMB);
        update_tri_layer(_META, _SYMB, _GAME);
      } else {
        layer_off(_SYMB);
        update_tri_layer(_META, _SYMB, _GAME);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        layer_on(_GAME);
      } else {
        layer_off(_GAME);
      }
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        register_code(KC_LANG2);
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        register_code(KC_LANG1);
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
  }
  return true;
}