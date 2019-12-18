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
 scalar_t__ EEPROM_MAGIC ; 
 scalar_t__ EEPROM_MAGIC_ADDR ; 
 scalar_t__ EEPROM_VERSION ; 
 scalar_t__ EEPROM_VERSION_ADDR ; 
 scalar_t__ eeprom_read_byte (void*) ; 
 scalar_t__ eeprom_read_word (void*) ; 

bool eeprom_is_valid(void)
{
	return (eeprom_read_word(((void*)EEPROM_MAGIC_ADDR)) == EEPROM_MAGIC &&
			eeprom_read_byte(((void*)EEPROM_VERSION_ADDR)) == EEPROM_VERSION);
}