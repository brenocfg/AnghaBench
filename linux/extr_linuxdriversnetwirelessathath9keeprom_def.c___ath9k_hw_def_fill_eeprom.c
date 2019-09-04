#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  def; } ;
struct ath_hw {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int SIZE_EEPROM_DEF ; 
 int /*<<< orphan*/  ath9k_hw_nvram_read (struct ath_hw*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __ath9k_hw_def_fill_eeprom(struct ath_hw *ah)
{
	u16 *eep_data = (u16 *)&ah->eeprom.def;
	int addr, ar5416_eep_start_loc = 0x100;

	for (addr = 0; addr < SIZE_EEPROM_DEF; addr++) {
		if (!ath9k_hw_nvram_read(ah, addr + ar5416_eep_start_loc,
					 eep_data))
			return false;
		eep_data++;
	}
	return true;
}