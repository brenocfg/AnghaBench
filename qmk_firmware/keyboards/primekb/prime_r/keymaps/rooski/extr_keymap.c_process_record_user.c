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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  AR_DN 132 
#define  AR_LT 131 
#define  AR_RT 130 
#define  AR_TOG 129 
#define  AR_UP 128 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_UP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_DOWN ; 
 int /*<<< orphan*/  X_KP_0 ; 
 int /*<<< orphan*/  X_KP_2 ; 
 int /*<<< orphan*/  X_KP_DOT ; 
 int /*<<< orphan*/  X_KP_ENTER ; 
 int /*<<< orphan*/  X_LEFT ; 
 int /*<<< orphan*/  X_RIGHT ; 
 int /*<<< orphan*/  X_UP ; 
 int arrow_toggle ; 
 int /*<<< orphan*/  backlight_toggle () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(record->event.pressed){
    switch(keycode) {
      case AR_TOG:
        arrow_toggle = !arrow_toggle;
        backlight_toggle();
        return false; break;

      case AR_UP:
        if(arrow_toggle == 1){
          SEND_STRING(SS_DOWN(X_UP));
        } else {
          SEND_STRING(SS_DOWN(X_KP_2));
        }
        return false; break;

      case AR_DN:
        if(arrow_toggle == 1){
          SEND_STRING(SS_DOWN(X_DOWN));
        } else {
          SEND_STRING(SS_DOWN(X_KP_DOT));
        }
        return false; break;

      case AR_LT:
        if(arrow_toggle == 1){
          SEND_STRING(SS_DOWN(X_LEFT));
        } else {
          SEND_STRING(SS_DOWN(X_KP_0));
        }
        return false; break;

      case AR_RT:
        if(arrow_toggle == 1){
          SEND_STRING(SS_DOWN(X_RIGHT));
        } else {
          SEND_STRING(SS_DOWN(X_KP_ENTER));
        }
        return false; break;
    }
  }
  if(!record->event.pressed){
    switch(keycode) {
      case AR_UP:
        if(arrow_toggle == 1){
          SEND_STRING(SS_UP(X_UP));
        } else {
          SEND_STRING(SS_UP(X_KP_2));
        }
        return false; break;
      case AR_DN:
        if(arrow_toggle == 1){
          SEND_STRING(SS_UP(X_DOWN));
        } else {
          SEND_STRING(SS_UP(X_KP_DOT));
        }
        return false; break;
      case AR_LT:
        if(arrow_toggle == 1){
          SEND_STRING(SS_UP(X_LEFT));
        } else {
          SEND_STRING(SS_UP(X_KP_0));
        }
        return false; break;
      case AR_RT:
        if(arrow_toggle == 1){
          SEND_STRING(SS_UP(X_RIGHT));
        } else {
          SEND_STRING(SS_UP(X_KP_ENTER));
        }
        return false; break;
    }
  }
  return true;
}