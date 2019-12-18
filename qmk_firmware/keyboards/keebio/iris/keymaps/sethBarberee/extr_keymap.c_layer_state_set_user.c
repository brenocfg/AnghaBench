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
 int /*<<< orphan*/  HSV_BLUE ; 
 int /*<<< orphan*/  HSV_GREEN ; 
 int /*<<< orphan*/  HSV_ORANGE ; 
 int /*<<< orphan*/  HSV_RED ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_STATIC_GRADIENT ; 
#define  _ADJUST 131 
#define  _LOWER 130 
#define  _QWERTY 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_user(uint32_t state){
    switch(biton32(state)) {
      case _QWERTY:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
      case _LOWER:
        rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
      case _RAISE:
        rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
      case _ADJUST:
        rgblight_sethsv_noeeprom(HSV_ORANGE);
        break;
      default:
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 3);
        break;

    }
    return state;
}