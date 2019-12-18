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
 int /*<<< orphan*/  custom_backlight_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int,int,int) ; 

void matrix_init_user(void) {
    #ifdef BACKLIGHT_ENABLE
        custom_backlight_level(0);
    #endif
    #ifdef RGBLIGHT_ENABLE
        rgblight_mode(1);
        rgblight_sethsv_noeeprom(180,100,100);
    #endif
}