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
 int /*<<< orphan*/  EEPROM_MAGIC_ADDR ; 
 int /*<<< orphan*/  eeprom_update_word (int /*<<< orphan*/ ,int) ; 

void eeprom_set_valid(bool valid)
{
	eeprom_update_word(EEPROM_MAGIC_ADDR, valid ? EEPROM_MAGIC : 0xFFFF);
}