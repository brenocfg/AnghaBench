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
 scalar_t__ RGBLIGHT_MODE_BREATHING ; 
 int /*<<< orphan*/  rgblight_enable_noeeprom () ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (scalar_t__) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_red () ; 

void keyboard_post_init_user(void){
    rgblight_enable_noeeprom(); // enable the RGBs
    rgblight_sethsv_noeeprom_red(); // set to red
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // set to breathing
}