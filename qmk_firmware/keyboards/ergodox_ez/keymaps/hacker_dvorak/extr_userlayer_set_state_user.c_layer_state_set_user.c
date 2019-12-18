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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  ARROWS 137 
#define  CHORD 136 
#define  DVORAK 135 
#define  FIRMWARE 134 
#define  GAMING 133 
#define  LAYERS 132 
#define  MEDIA_FN 131 
#define  MOUSE 130 
#define  NUMPAD 129 
#define  PLOVER 128 
 int PLOVER_MODE ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_BREATHING ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_KNIGHT ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_STATIC_LIGHT ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plover_toggle () ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_blue () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_cyan () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_green () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_magenta () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_red () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_yellow () ; 

uint32_t layer_state_set_user(uint32_t state) {
    uint8_t layer = biton32(state);

    switch (layer) {
        case DVORAK:
            rgblight_sethsv_noeeprom_green();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        case PLOVER:
            rgblight_sethsv_noeeprom_red();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);

            if (!(PLOVER_MODE)) {
                plover_toggle();
                PLOVER_MODE = true;
            }

            break;

        case GAMING:
            rgblight_sethsv_noeeprom_red();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        case ARROWS:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        case MOUSE:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        case NUMPAD:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        case LAYERS:
            rgblight_sethsv_noeeprom_cyan();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        case MEDIA_FN:
            rgblight_sethsv_noeeprom_yellow();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        case CHORD:
            rgblight_sethsv_noeeprom_magenta();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        case FIRMWARE:
            rgblight_sethsv_noeeprom_magenta();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);

            if (PLOVER_MODE) {
                plover_toggle();
                PLOVER_MODE = false;
            }

            break;

        default:
            break;
    }

    return state;
}