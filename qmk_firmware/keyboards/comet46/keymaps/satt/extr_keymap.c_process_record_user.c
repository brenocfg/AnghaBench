#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {scalar_t__ pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  JIS2US 130 
#define  PSEUDO_US 129 
#define  QWERTY 128 
 int /*<<< orphan*/  _PSEUDO_US ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  action_pseudo_lut (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keymap_jis2us ; 
 int /*<<< orphan*/  set_keylog (int) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef SSD1306OLED
    if (record->event.pressed) {
      set_keylog(keycode);
    }
  #endif
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      break;
    case PSEUDO_US:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PSEUDO_US);
      }
      break;
    case JIS2US:
      action_pseudo_lut(record, _QWERTY, keymap_jis2us);
      break;
  }
  return true;
}