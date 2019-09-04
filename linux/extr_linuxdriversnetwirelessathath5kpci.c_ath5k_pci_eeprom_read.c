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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ath_common {scalar_t__ ah; } ;
struct ath5k_hw {scalar_t__ ah_version; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 scalar_t__ AR5K_EEPROM_BASE ; 
 int /*<<< orphan*/  AR5K_EEPROM_CMD ; 
 int /*<<< orphan*/  AR5K_EEPROM_CMD_READ ; 
 scalar_t__ AR5K_EEPROM_DATA ; 
 scalar_t__ AR5K_EEPROM_STATUS ; 
 int AR5K_EEPROM_STAT_RDDONE ; 
 int AR5K_EEPROM_STAT_RDERR ; 
 int /*<<< orphan*/  AR5K_PCICFG ; 
 int /*<<< orphan*/  AR5K_PCICFG_EEAE ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int AR5K_TUNE_REGISTER_TIMEOUT ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool
ath5k_pci_eeprom_read(struct ath_common *common, u32 offset, u16 *data)
{
	struct ath5k_hw *ah = (struct ath5k_hw *) common->ah;
	u32 status, timeout;

	/*
	 * Initialize EEPROM access
	 */
	if (ah->ah_version == AR5K_AR5210) {
		AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, AR5K_PCICFG_EEAE);
		(void)ath5k_hw_reg_read(ah, AR5K_EEPROM_BASE + (4 * offset));
	} else {
		ath5k_hw_reg_write(ah, offset, AR5K_EEPROM_BASE);
		AR5K_REG_ENABLE_BITS(ah, AR5K_EEPROM_CMD,
				AR5K_EEPROM_CMD_READ);
	}

	for (timeout = AR5K_TUNE_REGISTER_TIMEOUT; timeout > 0; timeout--) {
		status = ath5k_hw_reg_read(ah, AR5K_EEPROM_STATUS);
		if (status & AR5K_EEPROM_STAT_RDDONE) {
			if (status & AR5K_EEPROM_STAT_RDERR)
				return false;
			*data = (u16)(ath5k_hw_reg_read(ah, AR5K_EEPROM_DATA) &
					0xffff);
			return true;
		}
		usleep_range(15, 20);
	}

	return false;
}