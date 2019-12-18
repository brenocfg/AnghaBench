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
#define  DBG_KBD 133 
#define  DBG_MOU 132 
#define  DBG_MTRX 131 
#define  DBG_TOG 130 
 int /*<<< orphan*/  MODS_CTRL ; 
 int /*<<< orphan*/  MODS_SHIFT ; 
 int /*<<< orphan*/  TOGGLE_FLAG_AND_PRINT (int /*<<< orphan*/ ,char*) ; 
#define  U_T_AGCR 129 
#define  U_T_AUTO 128 
 int /*<<< orphan*/  debug_enable ; 
 int /*<<< orphan*/  debug_keyboard ; 
 int /*<<< orphan*/  debug_matrix ; 
 int /*<<< orphan*/  debug_mouse ; 
 int /*<<< orphan*/  usb_extra_manual ; 
 int /*<<< orphan*/  usb_gcr_auto ; 

bool process_record_keymap(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL)
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL)
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            return false;
        case DBG_TOG:
            if (record->event.pressed)
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            return false;
        case DBG_MTRX:
            if (record->event.pressed)
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            return false;
        case DBG_KBD:
            if (record->event.pressed)
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            return false;
        case DBG_MOU:
            if (record->event.pressed)
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            return false;
    }

    return true;
}