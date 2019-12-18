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
typedef  int /*<<< orphan*/  layer_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  is_overwatch; scalar_t__ rgb_layer_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGBLIGHT_MODE_BREATHING ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_KNIGHT ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_SNAKE ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_STATIC_LIGHT ; 
#define  _ADJUST 141 
#define  _CARPLAX 140 
#define  _COLEMAK 139 
#define  _DIABLO 138 
#define  _DVORAK 137 
#define  _EUCALYN 136 
#define  _GAMEPAD 135 
#define  _LOWER 134 
#define  _MACROS 133 
#define  _MALTRON 132 
#define  _MEDIA 131 
 int _MODS ; 
#define  _NORMAN 130 
#define  _RAISE 129 
#define  _WORKMAN 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_state ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_blue () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_chartreuse () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_coral () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_cyan () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_goldenrod () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_green () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_magenta () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_orange () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_pink () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_red () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_springgreen () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_yellow () ; 
 TYPE_1__ userspace_config ; 

layer_state_t layer_state_set_rgb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    if (userspace_config.rgb_layer_change) {
        switch (biton32(state)) {
            case _MACROS:
                rgblight_sethsv_noeeprom_orange();
                userspace_config.is_overwatch ? rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 2) : rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 3);
                break;
            case _MEDIA:
                rgblight_sethsv_noeeprom_chartreuse();
                rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 1);
                break;
            case _GAMEPAD:
                rgblight_sethsv_noeeprom_orange();
                rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 2);
                break;
            case _DIABLO:
                rgblight_sethsv_noeeprom_red();
                rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
                break;
            case _RAISE:
                rgblight_sethsv_noeeprom_yellow();
                rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
                break;
            case _LOWER:
                rgblight_sethsv_noeeprom_green();
                rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
                break;
            case _ADJUST:
                rgblight_sethsv_noeeprom_red();
                rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);
                break;
            default:  //  for any other layers, or the default layer
                switch (biton32(default_layer_state)) {
                    case _COLEMAK:
                        rgblight_sethsv_noeeprom_magenta();
                        break;
                    case _DVORAK:
                        rgblight_sethsv_noeeprom_springgreen();
                        break;
                    case _WORKMAN:
                        rgblight_sethsv_noeeprom_goldenrod();
                        break;
                    case _NORMAN:
                        rgblight_sethsv_noeeprom_coral();
                        break;
                    case _MALTRON:
                        rgblight_sethsv_noeeprom_yellow();
                        break;
                    case _EUCALYN:
                        rgblight_sethsv_noeeprom_pink();
                        break;
                    case _CARPLAX:
                        rgblight_sethsv_noeeprom_blue();
                        break;
                    default:
                        rgblight_sethsv_noeeprom_cyan();
                        break;
                }
                biton32(state) == _MODS ? rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING) : rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);  // if _MODS layer is on, then breath to denote it
                break;
        }
    }
#endif  // RGBLIGHT_ENABLE

    return state;
}