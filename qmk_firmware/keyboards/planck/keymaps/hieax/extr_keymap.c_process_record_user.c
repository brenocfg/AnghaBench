#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_13__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  AT_DOWN 167 
#define  BASE1 166 
#define  BASE2 165 
 int BASE_1 ; 
 int BASE_12 ; 
 int BASE_2 ; 
#define  CNTR_BL 164 
#define  CNTR_BR 163 
#define  CNTR_HL 162 
#define  CNTR_HR 161 
#define  CNTR_TL 160 
#define  CNTR_TR 159 
#define  CT_RGHT 158 
#define  GT_UP 157 
#define  HOME_A 156 
#define  HOME_E 155 
#define  HOME_H 154 
#define  HOME_I 153 
#define  HOME_R 152 
#define  HOME_S 151 
#define  HOME_T 150 
#define  HOME_W 149 
 int /*<<< orphan*/  KC_4 ; 
 int /*<<< orphan*/  KC_5 ; 
 int /*<<< orphan*/  KC_6 ; 
 int /*<<< orphan*/  KC_A ; 
 int /*<<< orphan*/  KC_DEL ; 
 int /*<<< orphan*/  KC_G ; 
 int /*<<< orphan*/  KC_H ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LEFT ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  KC_SPC ; 
 int /*<<< orphan*/  KC_T ; 
 int /*<<< orphan*/  KC_TAB ; 
 int /*<<< orphan*/  KC_W ; 
 int /*<<< orphan*/  LEFT ; 
#define  LT_BSLS 148 
#define  LT_ESC 147 
#define  LT_LEFT 146 
 int /*<<< orphan*/  NOSHIFT ; 
#define  OS_ALT 145 
#define  OS_CTL 144 
#define  OS_GUI 143 
#define  PLOVER 142 
 int /*<<< orphan*/  RIGHT ; 
 int /*<<< orphan*/  SHIFT ; 
#define  SL_LEFT 141 
#define  SL_SPC 140 
#define  SL_TAB 139 
#define  SM_CIRC 138 
#define  SM_DLR 137 
#define  SM_G 136 
#define  SM_H 135 
#define  SM_PERC 134 
#define  SM_W 133 
#define  SP_BSPC 132 
#define  SP_DEL 131 
#define  TD_ENT 130 
#define  TD_SPC 129 
#define  TT_ESC 128 
 int /*<<< orphan*/  _FNCKEY ; 
 int /*<<< orphan*/  _LSHIFT ; 
 int /*<<< orphan*/  _MOUSE ; 
 int /*<<< orphan*/  _NUMBER ; 
 int /*<<< orphan*/  _RSHIFT ; 
 int /*<<< orphan*/  _SYMBOL ; 
 int /*<<< orphan*/  base_layer () ; 
 int base_n ; 
 int /*<<< orphan*/  clear_tt () ; 
 int /*<<< orphan*/  lt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lt_shift (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_shift (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  steno (TYPE_2__*) ; 
 int /*<<< orphan*/  symbol_shift (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_layer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_mods (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thumb_layer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tt_keycode ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    case BASE1:
      if (record->event.pressed) {
        base_n = base_n | BASE_1;
        if (base_n == BASE_12) {
          base_layer();
        }
      }
      else {
        base_n = base_n & ~BASE_1;
      }
      return false;
    case BASE2:
      if (record->event.pressed) {
        base_n = base_n | BASE_2;
        if (base_n == BASE_12) {
          base_layer();
        }
      }
      else {
        base_n = base_n & ~BASE_2;
      }
      return false;
#ifdef HOME_MODS
    case HOME_E:
    case HOME_R:
      tap_mods(record, KC_LALT);
      symbol_shift(record, 0);
      break;
    case HOME_H:
    case HOME_W:
      tap_mods(record, KC_LGUI);
      symbol_shift(record, 0);
      break;
    case HOME_I:
    case HOME_S:
      tap_mods(record, KC_LCTL);
      symbol_shift(record, 0);
      break;
    case HOME_A:
      tap_mods(record, KC_LSFT);
      symbol_shift(record, KC_A);
      break;
    case HOME_T:
      tap_mods(record, KC_RSFT);
      symbol_shift(record, KC_T);
      break;
#else
    case AT_DOWN:
      tap_mods(record, KC_LALT);
      break;
    case CT_RGHT:
      tap_mods(record, KC_LGUI);
      break;
    case GT_UP:
      tap_mods(record, KC_LCTL);
      break;
#endif
    case SL_SPC:
      lt(record, NOSHIFT, KC_SPC, KC_LSFT, _SYMBOL);
      break;
#ifdef CENTER_TT
    case TT_ESC:
      clear_tt();                           // exit TT layer
      return false;
#endif
    case LT_ESC:
#ifdef CENTER_TT
      if (tt_keycode != 0) {
        clear_tt();                         // exit TT layer
        return false;
      }
#endif
      tap_layer(record, _NUMBER);
      break;
    case LT_LEFT:
    case SP_BSPC:
      tap_layer(record, _SYMBOL);
      // LT (_SYMBOL, KC_LEFT) left right combination layer
      thumb_layer(record, RIGHT, 0, 0, _SYMBOL, _LSHIFT);
      break;
    case OS_ALT:
      tap_mods(record, KC_LALT);
      break;
    case OS_CTL:
      tap_mods(record, KC_LCTL);
      break;
    case OS_GUI:
      tap_mods(record, KC_LGUI);
      break;
    case SM_CIRC:
      // GUI_T(S(KC_6))
      mt_shift(record, KC_LGUI, 0, KC_6);
      break;
    case SM_DLR:
      // SFT_T(S(KC_4))
      mt_shift(record, KC_LSFT, 0, KC_4);
      break;
    case SM_G:
      // MT(MOD_LALT | MOD_LSFT, S(KC_G))
      mt_shift(record, KC_LALT, KC_LSFT, KC_G);
      break;
    case SM_H:
      // MT(MOD_LCTL | MOD_LSFT, S(KC_K))
      mt_shift(record, KC_LCTL, KC_LSFT, KC_H);
      break;
    case SM_W:
      // MT(MOD_LGUI | MOD_LSFT, S(KC_W))
      mt_shift(record, KC_LGUI, KC_LSFT, KC_W);
      break;
    case SM_PERC:
      // ALT_T(S(KC_5))
      mt_shift(record, KC_LALT, 0, KC_5);
      break;
    case LT_BSLS:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, KC_BSLS) left right combination layer, see #define LT_BSLS
      thumb_layer(record, LEFT, 0, 0, _MOUSE, _SYMBOL);
      break;
    case SL_LEFT:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_LEFT)) left right combination layer
      thumb_layer(record, RIGHT, SHIFT, KC_LEFT, _MOUSE, _LSHIFT);
      break;
    case SP_DEL:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_LEFT)) left right combination layer
      thumb_layer(record, RIGHT, NOSHIFT, KC_DEL, _MOUSE, _LSHIFT);
      break;
    case SL_TAB:
      // LT (_FNCKEY, S(KC_TAB)) emulation
      lt_shift(record, KC_TAB, _FNCKEY);
      break;
    case TD_ENT:
      tap_layer(record, _RSHIFT);
      // LT (_RSHIFT, KC_ENT) emulation, see tap dance enter
      break;
    case TD_SPC:
      tap_layer(record, _LSHIFT);
      // LT (_LSHIFT, KC_SPC) left right combination layer, see tap dance TD_SPC
      thumb_layer(record, LEFT, 0, 0, _LSHIFT, _SYMBOL);
      break;
#ifdef CENTER_TT
    case CNTR_TL:
    case CNTR_TR:
    case CNTR_HL:
    case CNTR_HR:
    case CNTR_BL:
    case CNTR_BR:
      if (tt_keycode != keycode && tt_keycode != 0) {
        clear_tt();                         // return to base layer first if different TT layer selected
      }
      tt_keycode = keycode;
      break;
#endif
// #ifdef STENO_ENABLE
//     case PS_STNA:
//       stn_layer(record, STN_A, _NUMBER);
//       break;
//     case PS_STNO:
//       stn_layer(record, STN_O, _FNCKEY);
//       break;
//     case PS_STNE:
//       stn_layer(record, STN_E, _EDIT);
//       break;
//     case PS_STNU:
//       stn_layer(record, STN_U, _SYMBOL);
//       break;
// #endif
    case PLOVER:
      steno(record);
      return false;
  }
  return true;
}