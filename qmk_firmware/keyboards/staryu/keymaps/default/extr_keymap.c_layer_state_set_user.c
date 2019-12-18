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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  _LAYER0 132 
#define  _LAYER1 131 
#define  _LAYER2 130 
#define  _LAYER3 129 
#define  _LAYER4 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_cyan () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_magenta () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_orange () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_red () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_white () ; 

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _LAYER1:
        rgblight_sethsv_noeeprom_cyan();
        break;
    case _LAYER2:
        rgblight_sethsv_noeeprom_magenta();
        break;
    case _LAYER3:
        rgblight_sethsv_noeeprom_red();
        break;
    case _LAYER4:
        rgblight_sethsv_noeeprom_orange();
        break;
    case _LAYER0:
    default: //  for any other layers, or the default layer
        rgblight_sethsv_noeeprom_white();
        break;
    }
  return state;
}