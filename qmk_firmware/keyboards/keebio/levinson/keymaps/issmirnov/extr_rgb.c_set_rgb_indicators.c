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

/* Variables and functions */
 int /*<<< orphan*/  GUI_LED1 ; 
 int MOD_MASK_GUI ; 
 int MOD_MASK_SHIFT ; 
 int /*<<< orphan*/  RGB_CLEAR ; 
 int /*<<< orphan*/  SHFT_LED1 ; 
 scalar_t__ _QWERTY ; 
 scalar_t__ biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  rgblight_setrgb_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb_gold_at (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb_purple_at (int /*<<< orphan*/ ) ; 

void set_rgb_indicators(uint8_t this_mod, uint8_t this_osm) {
  if (biton32(layer_state) == _QWERTY) {
    if ((this_mod | this_osm) & MOD_MASK_SHIFT) {
      rgblight_setrgb_gold_at(SHFT_LED1);
    } else {
      rgblight_setrgb_at(RGB_CLEAR, SHFT_LED1);
    }

    if ((this_mod | this_osm) & MOD_MASK_GUI) {
      rgblight_setrgb_purple_at(GUI_LED1);
    } else {
      rgblight_setrgb_at(RGB_CLEAR, GUI_LED1);
    }
  }
}