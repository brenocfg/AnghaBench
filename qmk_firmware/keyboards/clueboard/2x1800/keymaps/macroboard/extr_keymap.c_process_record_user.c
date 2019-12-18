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
#define  MACRO01 148 
#define  MACRO02 147 
#define  MACRO03 146 
#define  MACRO04 145 
#define  MACRO05 144 
#define  MACRO06 143 
#define  MACRO07 142 
#define  MACRO08 141 
#define  MACRO09 140 
#define  MACRO10 139 
#define  MACRO11 138 
#define  MACRO12 137 
#define  MACRO13 136 
#define  MACRO14 135 
#define  MACRO15 134 
#define  MACRO16 133 
#define  MACRO17 132 
#define  MACRO18 131 
#define  MACRO19 130 
#define  MACRO20 129 
#define  MACRO21 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case MACRO01:
                SEND_STRING("This is macro 01");
                return false;
            case MACRO02:
                SEND_STRING("This is macro 02");
                return false;
            case MACRO03:
                SEND_STRING("This is macro 03");
                return false;
            case MACRO04:
                SEND_STRING("This is macro 04");
                return false;
            case MACRO05:
                SEND_STRING("This is macro 05");
                return false;
            case MACRO06:
                SEND_STRING("This is macro 06");
                return false;
            case MACRO07:
                SEND_STRING("This is macro 07");
                return false;
            case MACRO08:
                SEND_STRING("This is macro 08");
                return false;
            case MACRO09:
                SEND_STRING("This is macro 09");
                return false;
            case MACRO10:
                SEND_STRING("This is macro 10");
                return false;
            case MACRO11:
                SEND_STRING("This is macro 11");
                return false;
            case MACRO12:
                SEND_STRING("This is macro 12");
                return false;
            case MACRO13:
                SEND_STRING("This is macro 13");
                return false;
            case MACRO14:
                SEND_STRING("This is macro 14");
                return false;
            case MACRO15:
                SEND_STRING("This is macro 15");
                return false;
            case MACRO16:
                SEND_STRING("This is macro 16");
                return false;
            case MACRO17:
                SEND_STRING("This is macro 17");
                return false;
            case MACRO18:
                SEND_STRING("This is macro 18");
                return false;
            case MACRO19:
                SEND_STRING("This is macro 19");
                return false;
            case MACRO20:
                SEND_STRING("This is macro 20");
                return false;
            case MACRO21:
                SEND_STRING("This is macro 21");
                return false;
        }
    }
    return true;
}