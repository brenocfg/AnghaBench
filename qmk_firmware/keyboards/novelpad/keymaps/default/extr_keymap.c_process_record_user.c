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
#define  WK_BLUE 130 
#define  WK_GREEN 129 
#define  WK_RED 128 
 int /*<<< orphan*/  rgblight_show_solid_color (int,int,int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WK_RED:
            if (record->event.pressed) {
                rgblight_show_solid_color(0xFF, 0x00, 0x00);
            } else {
                rgblight_show_solid_color(0xFF, 0xFF, 0xFF);
            }
            return false;
        case WK_GREEN:
            if (record->event.pressed) {
                rgblight_show_solid_color(0x00, 0xFF, 0x00);
            } else {
                rgblight_show_solid_color(0xFF, 0xFF, 0xFF);
            }
            return false;
        case WK_BLUE:
            if (record->event.pressed) {
                rgblight_show_solid_color(0x00, 0x00, 0xFF);
            } else {
                rgblight_show_solid_color(0xFF, 0xFF, 0xFF);
            }
            return false;
    }
    return true;
}