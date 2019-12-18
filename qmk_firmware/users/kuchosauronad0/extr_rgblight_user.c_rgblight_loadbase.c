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
 int /*<<< orphan*/  base_hue ; 
 int /*<<< orphan*/  base_mod ; 
 int /*<<< orphan*/  base_sat ; 
 int /*<<< orphan*/  base_val ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_eeprom_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rgblight_loadbase(void) {  // Load settings from ram to eeprom
  rgblight_mode( base_mod );
  rgblight_sethsv_eeprom_helper(base_hue, base_sat, base_val, true);
}