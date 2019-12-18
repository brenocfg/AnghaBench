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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int /*<<< orphan*/  mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  KC_BSPC ; 
 int /*<<< orphan*/  KC_DEL ; 
#define  M_BSDEL 128 
 int /*<<< orphan*/  bsdel_mods ; 
 TYPE_4__* keyboard_report ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case M_BSDEL: {
        uint8_t kc = KC_BSPC;

        if (record->event.pressed) {
            if (keyboard_report->mods) {
                kc = KC_DEL;
            }
            register_code (kc);
            bsdel_mods = keyboard_report->mods;
        }
        else {
            if (bsdel_mods) {
                kc = KC_DEL;
            }
            unregister_code (kc);
        }

        return false;
        break;
    }
  }
  return true;
}