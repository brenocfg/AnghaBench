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
struct TYPE_2__ {scalar_t__ rgb_layer_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGBLIGHT_MODE_BREATHING ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_STATIC_LIGHT ; 
#define  _ADJUST 135 
#define  _COLEMAK 134 
#define  _DVORAK 133 
#define  _LOWER 132 
 int _MODS ; 
#define  _PLOVER 131 
#define  _QWERTY 130 
#define  _RAISE 129 
#define  _WORKMAN 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_state ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_blue () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_goldenrod () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_green () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_magenta () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_pink () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_red () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_white () ; 
 TYPE_1__ userspace_config ; 

layer_state_t layer_state_set_rgb(layer_state_t state) {
# ifdef RGBLIGHT_ENABLE
  if (userspace_config.rgb_layer_change) {
    switch (biton32(state)) {  // _RAISE, _LOWER and _ADJUST use a custom color and the breathing effect
      case _RAISE:
        rgblight_sethsv_noeeprom_green();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;
      case _LOWER:
        rgblight_sethsv_noeeprom_red();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;
      case _ADJUST:
        rgblight_sethsv_noeeprom_white();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
        break;
      default:  // Use a solid color for normal layers
        switch (biton32(default_layer_state)) {
          case _QWERTY:
            rgblight_sethsv_noeeprom_magenta();
            break;
          case _COLEMAK:
            rgblight_sethsv_noeeprom_green();
            break;
          case _DVORAK:
            rgblight_sethsv_noeeprom_blue();
            break;
          case _WORKMAN:
            rgblight_sethsv_noeeprom_goldenrod();
            break;
          case _PLOVER:
            rgblight_sethsv_noeeprom_pink();
            break;
          default:
            rgblight_sethsv_noeeprom_white();
            break;
        }
        biton32(state) == _MODS ? rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING) : rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);  // if _MODS layer is on, then breath to denote it
        break;
    }
  }
# endif  // !RGBLIGHT_ENABLE
  return state;
}