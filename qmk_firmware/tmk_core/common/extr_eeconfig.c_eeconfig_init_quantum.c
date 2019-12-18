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
 int /*<<< orphan*/  EECONFIG_AUDIO ; 
 int /*<<< orphan*/  EECONFIG_BACKLIGHT ; 
 int /*<<< orphan*/  EECONFIG_DEBUG ; 
 int /*<<< orphan*/  EECONFIG_DEFAULT_LAYER ; 
 int /*<<< orphan*/  EECONFIG_HANDEDNESS ; 
 int /*<<< orphan*/  EECONFIG_HAPTIC ; 
 int /*<<< orphan*/  EECONFIG_KEYMAP_LOWER_BYTE ; 
 int /*<<< orphan*/  EECONFIG_KEYMAP_UPPER_BYTE ; 
 int /*<<< orphan*/  EECONFIG_MAGIC ; 
 int /*<<< orphan*/  EECONFIG_MAGIC_NUMBER ; 
 int /*<<< orphan*/  EECONFIG_MOUSEKEY_ACCEL ; 
 int /*<<< orphan*/  EECONFIG_RGBLIGHT ; 
 int /*<<< orphan*/  EECONFIG_RGB_MATRIX ; 
 int /*<<< orphan*/  EECONFIG_RGB_MATRIX_SPEED ; 
 int /*<<< orphan*/  EECONFIG_STENOMODE ; 
 int /*<<< orphan*/  EECONFIG_VELOCIKEY ; 
 int /*<<< orphan*/  EEPROM_Erase () ; 
 scalar_t__ default_layer_state ; 
 int /*<<< orphan*/  eeconfig_init_kb () ; 
 int /*<<< orphan*/  eeprom_update_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eeprom_update_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_update_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void eeconfig_init_quantum(void) {
#ifdef STM32_EEPROM_ENABLE
    EEPROM_Erase();
#endif
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER);
    eeprom_update_byte(EECONFIG_DEBUG, 0);
    eeprom_update_byte(EECONFIG_DEFAULT_LAYER, 0);
    default_layer_state = 0;
    eeprom_update_byte(EECONFIG_KEYMAP_LOWER_BYTE, 0);
    eeprom_update_byte(EECONFIG_KEYMAP_UPPER_BYTE, 0);
    eeprom_update_byte(EECONFIG_MOUSEKEY_ACCEL, 0);
    eeprom_update_byte(EECONFIG_BACKLIGHT, 0);
    eeprom_update_byte(EECONFIG_AUDIO, 0xFF);  // On by default
    eeprom_update_dword(EECONFIG_RGBLIGHT, 0);
    eeprom_update_byte(EECONFIG_STENOMODE, 0);
    eeprom_update_dword(EECONFIG_HAPTIC, 0);
    eeprom_update_byte(EECONFIG_VELOCIKEY, 0);
    eeprom_update_dword(EECONFIG_RGB_MATRIX, 0);
    eeprom_update_byte(EECONFIG_RGB_MATRIX_SPEED, 0);

    // TODO: Remove once ARM has a way to configure EECONFIG_HANDEDNESS
    //        within the emulated eeprom via dfu-util or another tool
#if defined INIT_EE_HANDS_LEFT
#    pragma message "Faking EE_HANDS for left hand"
    eeprom_update_byte(EECONFIG_HANDEDNESS, 1);
#elif defined INIT_EE_HANDS_RIGHT
#    pragma message "Faking EE_HANDS for right hand"
    eeprom_update_byte(EECONFIG_HANDEDNESS, 0);
#endif

    eeconfig_init_kb();
}