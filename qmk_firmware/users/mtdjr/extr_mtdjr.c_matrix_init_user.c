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
 int /*<<< orphan*/  RGB_HUE ; 
 int /*<<< orphan*/  RGB_MODE ; 
 int /*<<< orphan*/  rgblight_enable_noeeprom () ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  solenoid_setup () ; 

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGB_MODE);
    rgblight_sethsv (RGB_HUE, 255, 255);
  #endif
  #ifdef SOLENOID_ENABLE
    solenoid_setup();
  #endif
}