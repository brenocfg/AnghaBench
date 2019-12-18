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
#define  EQL 131 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
#define  nav 130 
#define  num 129 
#define  qwerty 128 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case qwerty:
                SEND_STRING("-QWERTY");
                return false;
            case nav:
                SEND_STRING("-NAV"); // selects all and copies
                return false;
            case num:
                SEND_STRING("-NUM"); // selects all and copies
                return false;
            case EQL:
                SEND_STRING("="); // selects all and copies
                return false;
        }
    }
    return true;
}