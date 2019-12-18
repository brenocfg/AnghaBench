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

/* Variables and functions */
 int /*<<< orphan*/  HSV_BLUE ; 
 int /*<<< orphan*/  HSV_CORAL ; 
 int /*<<< orphan*/  HSV_MAGENTA ; 
 int /*<<< orphan*/  HSV_WHITE ; 
 scalar_t__ IS_HOST_LED_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
#define  _BASE 130 
#define  _L 129 
#define  _R 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_range (int /*<<< orphan*/ ,int,int) ; 

void update_led(void) {
    switch (biton32(layer_state)) {
    case _BASE:
      rgblight_sethsv_noeeprom(HSV_BLUE);
      break;
    case _L:
      rgblight_sethsv_noeeprom(HSV_CORAL);
      break;
    case _R:
      rgblight_sethsv_noeeprom(HSV_MAGENTA);
      break;
    }
  if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
    rgblight_sethsv_range(HSV_WHITE,0,3);
    rgblight_sethsv_range(HSV_WHITE,9,12);
  }
}