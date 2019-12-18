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
#define  COLEMAK 132 
#define  DESTINY 131 
#define  DVORAK 130 
#define  QWERTY 129 
#define  WOW 128 
 int /*<<< orphan*/  _COLEMAK ; 
 int /*<<< orphan*/  _DESTINY ; 
 int /*<<< orphan*/  _DVORAK ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _WOW ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
   switch (keycode) {
    case DVORAK:
        set_single_persistent_default_layer(_DVORAK);
      return false;
    case QWERTY:
        set_single_persistent_default_layer(_QWERTY);
      return false;
    case COLEMAK:
        set_single_persistent_default_layer(_COLEMAK);
      return false;
    case WOW:
        set_single_persistent_default_layer(_WOW);
      return false;
    case DESTINY:
        set_single_persistent_default_layer(_DESTINY);
      return false;
   }
  }
  return true;
}