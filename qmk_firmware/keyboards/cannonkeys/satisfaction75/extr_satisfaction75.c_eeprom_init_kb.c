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
 int /*<<< orphan*/  dynamic_keymap_custom_reset () ; 
 int /*<<< orphan*/  dynamic_keymap_macro_reset () ; 
 int /*<<< orphan*/  dynamic_keymap_reset () ; 
 scalar_t__ eeprom_is_valid () ; 
 int /*<<< orphan*/  eeprom_set_valid (int) ; 
 int /*<<< orphan*/  load_custom_config () ; 

void eeprom_init_kb(void)
{
	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (eeprom_is_valid()) {
		load_custom_config();
	} else	{
		// If the EEPROM has not been saved before, or is out of date,
		// save the default values to the EEPROM. Default values
		// come from construction of the zeal_backlight_config instance.
		//backlight_config_save();
#ifdef DYNAMIC_KEYMAP_ENABLE
		// This resets the keymaps in EEPROM to what is in flash.
		dynamic_keymap_reset();
		// This resets the macros in EEPROM to nothing.
		dynamic_keymap_macro_reset();
    // Reset the custom stuff
    dynamic_keymap_custom_reset();
#endif
		// Save the magic number last, in case saving was interrupted
		eeprom_set_valid(true);
	}
}