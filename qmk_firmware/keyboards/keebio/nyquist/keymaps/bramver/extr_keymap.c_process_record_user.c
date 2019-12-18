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
#define  CTRL_C 131 
#define  CTRL_V 130 
#define  CTRL_X 129 
#define  CTRL_Z 128 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_LCTRL (char*) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
    switch(keycode) {
      case CTRL_Z:
        SEND_STRING(SS_LCTRL("z"));
        return false;
      case CTRL_X:
        SEND_STRING(SS_LCTRL("x"));
        return false;
      case CTRL_C:
        SEND_STRING(SS_LCTRL("c"));
        return false;
      case CTRL_V:
        SEND_STRING(SS_LCTRL("v"));
        return false;
    }
  }

  return true;
}