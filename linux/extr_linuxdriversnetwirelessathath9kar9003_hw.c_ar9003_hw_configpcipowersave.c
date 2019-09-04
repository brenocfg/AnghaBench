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
typedef  int u32 ;
struct ar5416IniArray {unsigned int ia_rows; } ;
struct TYPE_2__ {int aspm_l1_fix; } ;
struct ath_hw {int WARegVal; struct ar5416IniArray iniPcieSerdesLowPower; struct ar5416IniArray iniPcieSerdes; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PCIE_PM_CTRL ; 
 int /*<<< orphan*/  AR_PCIE_PM_CTRL_ENA ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 int AR_WA ; 
 int INI_RA (struct ar5416IniArray*,unsigned int,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 

__attribute__((used)) static void ar9003_hw_configpcipowersave(struct ath_hw *ah,
					 bool power_off)
{
	unsigned int i;
	struct ar5416IniArray *array;

	/*
	 * Increase L1 Entry Latency. Some WB222 boards don't have
	 * this change in eeprom/OTP.
	 *
	 */
	if (AR_SREV_9462(ah)) {
		u32 val = ah->config.aspm_l1_fix;
		if ((val & 0xff000000) == 0x17000000) {
			val &= 0x00ffffff;
			val |= 0x27000000;
			REG_WRITE(ah, 0x570c, val);
		}
	}

	/* Nothing to do on restore for 11N */
	if (!power_off /* !restore */) {
		/* set bit 19 to allow forcing of pcie core into L1 state */
		REG_SET_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);
		REG_WRITE(ah, AR_WA, ah->WARegVal);
	}

	/*
	 * Configire PCIE after Ini init. SERDES values now come from ini file
	 * This enables PCIe low power mode.
	 */
	array = power_off ? &ah->iniPcieSerdes :
		&ah->iniPcieSerdesLowPower;

	for (i = 0; i < array->ia_rows; i++) {
		REG_WRITE(ah,
			  INI_RA(array, i, 0),
			  INI_RA(array, i, 1));
	}
}