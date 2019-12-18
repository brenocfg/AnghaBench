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
 int /*<<< orphan*/  KC_LEFT ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_RIGHT ; 
#define  KI_1 144 
#define  KI_10 143 
#define  KI_11 142 
#define  KI_12 141 
#define  KI_2 140 
#define  KI_3 139 
#define  KI_4 138 
#define  KI_5 137 
#define  KI_6 136 
#define  KI_7 135 
#define  KI_8 134 
#define  KI_9 133 
#define  KI_BKSP 132 
#define  KI_BSLS 131 
#define  KI_ESC 130 
#define  KI_WLFT 129 
#define  KI_WRGT 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int is_lgui_active ; 
 int /*<<< orphan*/  lgui_timer ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Keycodes Starting with KI_ are place holders for my personal macros. They are set below. Most are simple SEND_STRINGS().
    case KI_ESC:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_1:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_2:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_3:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_4:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_5:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_6:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_7:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_8:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_9:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_10:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_11:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_12:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_BKSP:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key
    case KI_BSLS:
      if (record->event.pressed) {
        SEND_STRING("");
      } else {
        
      }
      return false; // Skip all further processing of this key

    //Windows Win+Left tap to move window without resetting KC_LGUI
    //Additional code is in matrix_scan_user()
    case KI_WLFT:
      if (record->event.pressed) {
        if (!is_lgui_active) {
          is_lgui_active = true;
          register_code(KC_LGUI);
        } 
        lgui_timer = timer_read();
        tap_code(KC_LEFT);
      } else {
        
      }
      return false; // Skip all further processing of this key
    //Windows Win+Right tap to move window without resetting KC_LGUI
    //Additional code is in matrix_scan_user()
    case KI_WRGT:
      if (record->event.pressed) {
        if (!is_lgui_active) {
          is_lgui_active = true;
          register_code(KC_LGUI);
        } 
        lgui_timer = timer_read();
        tap_code(KC_RIGHT);
      } else {
        
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}