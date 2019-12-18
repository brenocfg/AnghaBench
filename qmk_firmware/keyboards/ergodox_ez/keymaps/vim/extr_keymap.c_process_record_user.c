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
struct TYPE_7__ {int mods; } ;

/* Variables and functions */
#define  EPRM 152 
 int /*<<< orphan*/  INSERT_MODE ; 
 int /*<<< orphan*/  KC_LSFT ; 
#define  KC_NO 151 
 int /*<<< orphan*/  KC_RSFT ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
#define  RGB_SLD 150 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERSION_STRING ; 
#define  VIM_A 149 
 int /*<<< orphan*/  VIM_APPEND () ; 
 int /*<<< orphan*/  VIM_APPEND_LINE () ; 
#define  VIM_B 148 
 int /*<<< orphan*/  VIM_BACK () ; 
#define  VIM_C 147 
 int /*<<< orphan*/  VIM_CHANGE_BACK () ; 
 int /*<<< orphan*/  VIM_CHANGE_DOWN () ; 
 int /*<<< orphan*/  VIM_CHANGE_END () ; 
 int /*<<< orphan*/  VIM_CHANGE_INNER_WORD () ; 
 int /*<<< orphan*/  VIM_CHANGE_LEFT () ; 
 int /*<<< orphan*/  VIM_CHANGE_LINE () ; 
 int /*<<< orphan*/  VIM_CHANGE_RIGHT () ; 
 int /*<<< orphan*/  VIM_CHANGE_UP () ; 
 int /*<<< orphan*/  VIM_CHANGE_WHOLE_LINE () ; 
 int /*<<< orphan*/  VIM_CHANGE_WORD () ; 
#define  VIM_CI 146 
 int /*<<< orphan*/  VIM_CUT () ; 
#define  VIM_D 145 
 int /*<<< orphan*/  VIM_DELETE_BACK () ; 
 int /*<<< orphan*/  VIM_DELETE_DOWN () ; 
 int /*<<< orphan*/  VIM_DELETE_END () ; 
 int /*<<< orphan*/  VIM_DELETE_INNER_WORD () ; 
 int /*<<< orphan*/  VIM_DELETE_LEFT () ; 
 int /*<<< orphan*/  VIM_DELETE_LINE () ; 
 int /*<<< orphan*/  VIM_DELETE_RIGHT () ; 
 int /*<<< orphan*/  VIM_DELETE_UP () ; 
 int /*<<< orphan*/  VIM_DELETE_WHOLE_LINE () ; 
 int /*<<< orphan*/  VIM_DELETE_WORD () ; 
#define  VIM_DI 144 
 int /*<<< orphan*/  VIM_DOWN () ; 
#define  VIM_E 143 
 int /*<<< orphan*/  VIM_END () ; 
#define  VIM_H 142 
#define  VIM_I 141 
#define  VIM_J 140 
 int /*<<< orphan*/  VIM_JOIN () ; 
#define  VIM_K 139 
#define  VIM_L 138 
 int /*<<< orphan*/  VIM_LEADER (int const) ; 
 int /*<<< orphan*/  VIM_LEFT () ; 
#define  VIM_O 137 
 int /*<<< orphan*/  VIM_OPEN () ; 
 int /*<<< orphan*/  VIM_OPEN_ABOVE () ; 
#define  VIM_P 136 
 int /*<<< orphan*/  VIM_PUT () ; 
 int /*<<< orphan*/  VIM_PUT_BEFORE () ; 
 int /*<<< orphan*/  VIM_QUEUE ; 
 int /*<<< orphan*/  VIM_RIGHT () ; 
#define  VIM_S 135 
 int /*<<< orphan*/  VIM_SUBSTITUTE () ; 
#define  VIM_U 134 
 int /*<<< orphan*/  VIM_UNDO () ; 
 int /*<<< orphan*/  VIM_UP () ; 
#define  VIM_V 133 
#define  VIM_VI 132 
 int /*<<< orphan*/  VIM_VISUAL_BACK () ; 
 int /*<<< orphan*/  VIM_VISUAL_DOWN () ; 
 int /*<<< orphan*/  VIM_VISUAL_END () ; 
 int /*<<< orphan*/  VIM_VISUAL_INNER_WORD () ; 
 int /*<<< orphan*/  VIM_VISUAL_LEFT () ; 
 int /*<<< orphan*/  VIM_VISUAL_RIGHT () ; 
 int /*<<< orphan*/  VIM_VISUAL_UP () ; 
 int /*<<< orphan*/  VIM_VISUAL_WORD () ; 
#define  VIM_W 131 
 int /*<<< orphan*/  VIM_WORD () ; 
#define  VIM_X 130 
#define  VIM_Y 129 
 int /*<<< orphan*/  VIM_YANK () ; 
 int /*<<< orphan*/  VIM_YANK_LINE () ; 
#define  VRSN 128 
 int /*<<< orphan*/  eeconfig_init () ; 
 TYPE_4__* keyboard_report ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool SHIFTED = (keyboard_report->mods & MOD_BIT(KC_LSFT)) |
                 (keyboard_report->mods & MOD_BIT(KC_RSFT));

  switch (keycode) {

    case VIM_A:
      if (record->event.pressed) { SHIFTED ? VIM_APPEND_LINE() : VIM_APPEND(); }
      return false;

    case VIM_B:
      if (record->event.pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: VIM_BACK(); break;
          case VIM_C: VIM_CHANGE_BACK(); break;
          case VIM_D: VIM_DELETE_BACK(); break;
          case VIM_V: VIM_VISUAL_BACK(); break;
        }
      }
      return false;

    case VIM_C:
      if (record->event.pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_CHANGE_LINE() : VIM_LEADER(VIM_C); break;
          case VIM_C: VIM_CHANGE_WHOLE_LINE(); break;
        }
      }
      return false;

    case VIM_D:
      if (record->event.pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_DELETE_LINE() : VIM_LEADER(VIM_D); break;
          case VIM_D: VIM_DELETE_WHOLE_LINE(); break;
        }
      }
      return false;

    case VIM_E:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_END(); break;
          case VIM_C: VIM_CHANGE_END(); break;
          case VIM_D: VIM_DELETE_END(); break;
          case VIM_V: VIM_VISUAL_END(); break;
        }
      }
      return false;

    case VIM_H:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_LEFT(); break;
          case VIM_C: VIM_CHANGE_LEFT(); break;
          case VIM_D: VIM_DELETE_LEFT(); break;
          case VIM_V: VIM_VISUAL_LEFT(); break;
        }
      }
      return false;

    case VIM_I:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: layer_on(INSERT_MODE); break;
          case VIM_C: VIM_LEADER(VIM_CI); break;
          case VIM_D: VIM_LEADER(VIM_DI); break;
          case VIM_V: VIM_LEADER(VIM_VI); break;
        }
      }
      return false;

    case VIM_J:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_JOIN() : VIM_DOWN(); break;
          case VIM_C: VIM_CHANGE_DOWN(); break;
          case VIM_D: VIM_DELETE_DOWN(); break;
          case VIM_V: VIM_VISUAL_DOWN(); break;
        }
      }
      return false;

    case VIM_K:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_UP(); break;
          case VIM_C: VIM_CHANGE_UP(); break;
          case VIM_D: VIM_DELETE_UP(); break;
          case VIM_V: VIM_VISUAL_UP(); break;
        }
      }
      return false;

    case VIM_L:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_RIGHT(); break;
          case VIM_C: VIM_CHANGE_RIGHT(); break;
          case VIM_D: VIM_DELETE_RIGHT(); break;
          case VIM_V: VIM_VISUAL_RIGHT(); break;
        }
      }
      return false;

    case VIM_O:
      if (record->event.pressed) { SHIFTED ? VIM_OPEN_ABOVE() : VIM_OPEN(); }
      return false;

    case VIM_P:
      if (record->event.pressed) { SHIFTED ? VIM_PUT_BEFORE() : VIM_PUT(); }
      return false;

    case VIM_S:
      if (record->event.pressed) { SHIFTED ? VIM_CHANGE_WHOLE_LINE() : VIM_SUBSTITUTE(); }
      return false;

    case VIM_U:
      if (record->event.pressed) { VIM_UNDO(); }
      return false;

    case VIM_V:
      if (record->event.pressed) { VIM_LEADER(VIM_V); }
      return false;

    case VIM_W:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_WORD(); break;
          case VIM_C: VIM_CHANGE_WORD(); break;
          case VIM_CI: VIM_CHANGE_INNER_WORD(); break;
          case VIM_D: VIM_DELETE_WORD(); break;
          case VIM_DI: VIM_DELETE_INNER_WORD(); break;
          case VIM_V: VIM_VISUAL_WORD(); break;
          case VIM_VI: VIM_VISUAL_INNER_WORD(); break;
        }
      }
      return false;

    case VIM_X:
      if (record->event.pressed) { VIM_CUT(); }
      return false;

    case VIM_Y:
      if (record->event.pressed) { SHIFTED ? VIM_YANK_LINE() : VIM_YANK(); }
      return false;

    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) { eeconfig_init(); }
      return false;
    case VRSN:
      if (record->event.pressed) { SEND_STRING(VERSION_STRING); }
      return false;
    case RGB_SLD:
      if (record->event.pressed) { rgblight_mode(1); }
      return false;
  }

  // End by clearing the queue unless keycode is a
  // if ((record->event.pressed) &&
  //     (keycode != VIM_I ||
  //     keycode != VIM_C ||
  //     keycode != VIM_D ||
  //     keycode != VIM_V)) {
  //   VIM_LEADER(KC_NO);
  // }

  return true;
}