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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EECONFIG_KEYMAP_LOWER_BYTE ; 
 int /*<<< orphan*/  EECONFIG_KEYMAP_UPPER_BYTE ; 
 int /*<<< orphan*/  eeprom_update_byte (int /*<<< orphan*/ ,int) ; 

void eeconfig_update_keymap(uint16_t val) {
    eeprom_update_byte(EECONFIG_KEYMAP_LOWER_BYTE, val & 0xFF);
    eeprom_update_byte(EECONFIG_KEYMAP_UPPER_BYTE, (val >> 8) & 0xFF);
}