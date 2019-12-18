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
 int /*<<< orphan*/  backlight_enable () ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (scalar_t__) ; 

void eeconfig_init_user(void) {
  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_BREATHING+1);

  backlight_enable();
}