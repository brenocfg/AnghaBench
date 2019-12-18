#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  val; int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ BASE ; 
#define  _ADJUST 128 
 int biton32 (scalar_t__) ; 
 int edit ; 
 int /*<<< orphan*/  rgblight_get_hue () ; 
 int /*<<< orphan*/  rgblight_get_mode () ; 
 int /*<<< orphan*/  rgblight_get_sat () ; 
 int /*<<< orphan*/  rgblight_get_val () ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 
 TYPE_1__ temp_config ; 

uint32_t layer_state_set_user(uint32_t state) {
    if (state == BASE && edit == true) {
        temp_config.hue  = rgblight_get_hue();
        temp_config.sat  = rgblight_get_sat();
        temp_config.val  = rgblight_get_val();
        edit = false;
    }

    switch (biton32(state)) {
        case _ADJUST:
            temp_config.mode = rgblight_get_mode();
            rgblight_mode_noeeprom(1);
            rgblight_setrgb(0xD3, 0x7F, 0xED);
            edit = true;
            break;
        default:
            rgblight_mode(temp_config.mode);
            rgblight_sethsv(temp_config.hue, temp_config.sat, temp_config.val);
            break;
    }
    return state;
}