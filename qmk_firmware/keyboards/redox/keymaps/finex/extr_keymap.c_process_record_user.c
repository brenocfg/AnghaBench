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
#define  ASC_BKT 142 
#define  ASC_CBRL 141 
#define  ASC_CBRR 140 
#define  ASC_CIRC 139 
#define  ASC_DAR 138 
#define  ASC_DQT 137 
#define  ASC_HAP 136 
#define  ASC_SAD 135 
#define  ASC_SAR 134 
#define  ASC_SQT 133 
#define  ASC_TILD 132 
#define  COLEMAKDHMK 131 
#define  COLEMAKDHMK_MAC 130 
#define  QWERTY 129 
#define  QWERTY_MAC 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 char* SS_LSFT (char*) ; 
 char* SS_RALT (char*) ; 
 int /*<<< orphan*/  _COLEMAKDHMK ; 
 int /*<<< orphan*/  _COLEMAKDHMK_MAC ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _QWERTY_MAC ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case ASC_SAR:
        SEND_STRING("->");
        return false;
      case ASC_DAR:
        SEND_STRING("=>");
        return false;
      case ASC_SQT:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("'"));
        return false;
      case ASC_DQT:
        // SS_RALT(SS_LSFT()): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT(SS_LSFT("\"")));
        return false;
      case ASC_CIRC:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("^"));
        return false;
      case ASC_TILD:
        // SS_RALT(SS_LSFT()): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT(SS_LSFT("~")));
        return false;
      case ASC_HAP:
        SEND_STRING(":-) ");
        return false;
      case ASC_SAD:
        SEND_STRING(":-( ");
        return false;
      case ASC_BKT:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("`"));
        return false;
      case ASC_CBRL:
        SEND_STRING("{");
        return false;
      case ASC_CBRR:
        SEND_STRING("}");
        return false;
      case QWERTY:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
      case COLEMAKDHMK:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_COLEMAKDHMK);
        }
        return false;
        break;
      case QWERTY_MAC:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_QWERTY_MAC);
        }
        return false;
        break;
      case COLEMAKDHMK_MAC:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_COLEMAKDHMK_MAC);
        }
        return false;
        break;
    }
  }
  return true;
}