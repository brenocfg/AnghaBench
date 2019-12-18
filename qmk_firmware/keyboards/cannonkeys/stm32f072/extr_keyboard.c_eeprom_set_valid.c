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
 int EEPROM_MAGIC ; 
 scalar_t__ EEPROM_MAGIC_ADDR ; 
 int EEPROM_VERSION ; 
 scalar_t__ EEPROM_VERSION_ADDR ; 
 int /*<<< orphan*/  eeprom_update_byte (void*,int) ; 
 int /*<<< orphan*/  eeprom_update_word (void*,int) ; 

void eeprom_set_valid(bool valid)
{
	eeprom_update_word(((void*)EEPROM_MAGIC_ADDR), valid ? EEPROM_MAGIC : 0xFFFF);
	eeprom_update_byte(((void*)EEPROM_VERSION_ADDR), valid ? EEPROM_VERSION : 0xFF);
}