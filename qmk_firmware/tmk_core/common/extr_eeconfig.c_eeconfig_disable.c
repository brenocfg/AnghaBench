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
 int /*<<< orphan*/  EECONFIG_MAGIC ; 
 int /*<<< orphan*/  EECONFIG_MAGIC_NUMBER_OFF ; 
 int /*<<< orphan*/  EEPROM_Erase () ; 
 int /*<<< orphan*/  eeprom_update_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void eeconfig_disable(void) {
#ifdef STM32_EEPROM_ENABLE
    EEPROM_Erase();
#endif
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER_OFF);
}