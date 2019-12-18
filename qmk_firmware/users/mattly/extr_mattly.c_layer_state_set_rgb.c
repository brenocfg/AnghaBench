#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSV_FUNCT ; 
 int /*<<< orphan*/  HSV_NAVNUM ; 
 int /*<<< orphan*/  HSV_SYMBOL ; 
#define  _FUNCT 131 
#define  _NAVNUM 130 
#define  _QWERTY 129 
#define  _SYMBOL 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_lights_default () ; 

void layer_state_set_rgb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
        case _QWERTY:
            set_lights_default();
            break;
        case _SYMBOL:
            rgblight_sethsv_noeeprom(HSV_SYMBOL);
            break;
        case _NAVNUM:
            rgblight_sethsv_noeeprom(HSV_NAVNUM);
            break;
        case _FUNCT:
            rgblight_sethsv_noeeprom(HSV_FUNCT);
            break;
    }
#endif
}