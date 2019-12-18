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
 int /*<<< orphan*/  backlight_config_load () ; 
 int /*<<< orphan*/  backlight_config_save () ; 
 int /*<<< orphan*/  backlight_init_drivers () ; 
 int /*<<< orphan*/  backlight_timer_enable () ; 
 int /*<<< orphan*/  backlight_timer_init () ; 
 int /*<<< orphan*/  dynamic_keymap_macro_reset () ; 
 int /*<<< orphan*/  dynamic_keymap_reset () ; 
 scalar_t__ eeprom_is_valid () ; 
 int /*<<< orphan*/  eeprom_set_valid (int) ; 

void main_init(void)
{
	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (eeprom_is_valid()) {
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
		backlight_config_load();
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
	} else	{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
		// If the EEPROM has not been saved before, or is out of date,
		// save the default values to the EEPROM. Default values
		// come from construction of the backlight_config instance.
		backlight_config_save();
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
#ifdef DYNAMIC_KEYMAP_ENABLE
		// This resets the keymaps in EEPROM to what is in flash.
		dynamic_keymap_reset();
		// This resets the macros in EEPROM to nothing.
		dynamic_keymap_macro_reset();
#endif // DYNAMIC_KEYMAP_ENABLE
		// Save the magic number last, in case saving was interrupted
		eeprom_set_valid(true);
	}
	
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
	// Initialize LED drivers for backlight.
	backlight_init_drivers();

	backlight_timer_init();
	backlight_timer_enable();
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
}