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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  DBG_KBD 139 
#define  DBG_MOU 138 
#define  DBG_MTRX 137 
#define  DBG_TOG 136 
#define  HK_COSL 135 
#define  LED_FLAG_ALL 134 
#define  LED_FLAG_KEYLIGHT 133 
 int const LED_FLAG_NONE ; 
#define  LED_FLAG_UNDERGLOW 132 
#define  MD_BOOT 131 
 int /*<<< orphan*/  MODS_CTRL ; 
 int /*<<< orphan*/  MODS_SHIFT ; 
#define  RGB_TOG 130 
 int /*<<< orphan*/  TOGGLE_FLAG_AND_PRINT (int /*<<< orphan*/ ,char*) ; 
#define  U_T_AGCR 129 
#define  U_T_AUTO 128 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  debug_enable ; 
 int /*<<< orphan*/  debug_keyboard ; 
 int /*<<< orphan*/  debug_matrix ; 
 int /*<<< orphan*/  debug_mouse ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  reset_oneshot_layer () ; 
 int /*<<< orphan*/  rgb_matrix_disable_noeeprom () ; 
 int /*<<< orphan*/  rgb_matrix_enable_noeeprom () ; 
 int /*<<< orphan*/  rgb_matrix_get_flags () ; 
 int /*<<< orphan*/  rgb_matrix_set_color_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgb_matrix_set_flags (int const) ; 
 int timer_elapsed32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read32 () ; 
 int /*<<< orphan*/  usb_extra_manual ; 
 int /*<<< orphan*/  usb_gcr_auto ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case HK_COSL:
            clear_keyboard();
            reset_oneshot_layer();
            return true;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}