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
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 scalar_t__ RGBLIGHT_EFFECT_BREATHING ; 
 int /*<<< orphan*/ * led ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (scalar_t__) ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  rgblight_set_effect_range (int,int) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int,int,int) ; 
 int /*<<< orphan*/  setrgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    // Set up RGB effects on _only_ the third LED (index 2)
    rgblight_set_effect_range(2, 1);
    // Set LED effects to breathing mode in a tealish blue color
    rgblight_sethsv_noeeprom(185, 255, 255);
    rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING + 2);

    // Init the first two LEDs to a static color
    setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
    setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
}