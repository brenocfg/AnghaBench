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
typedef  size_t u32 ;
struct ath_hw {int initPDADC; int PDADCdelta; int* originalGain; TYPE_1__* eep_ops; } ;
struct TYPE_2__ {scalar_t__ (* get_eeprom ) (struct ath_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t AR9280_TX_GAIN_TABLE_SIZE ; 
 int /*<<< orphan*/  AR_PHY_TX_GAIN ; 
 scalar_t__ AR_PHY_TX_GAIN_TBL1 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL4 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL_PD_AVG_OUT ; 
 int /*<<< orphan*/  EEP_DAC_HPWR_5G ; 
 int MS (size_t,int /*<<< orphan*/ ) ; 
 size_t REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9280_hw_olc_temp_compensation(struct ath_hw *ah)
{
	u32 rddata, i;
	int delta, currPDADC, regval;

	rddata = REG_READ(ah, AR_PHY_TX_PWRCTRL4);
	currPDADC = MS(rddata, AR_PHY_TX_PWRCTRL_PD_AVG_OUT);

	if (ah->initPDADC == 0 || currPDADC == 0)
		return;

	if (ah->eep_ops->get_eeprom(ah, EEP_DAC_HPWR_5G))
		delta = (currPDADC - ah->initPDADC + 4) / 8;
	else
		delta = (currPDADC - ah->initPDADC + 5) / 10;

	if (delta != ah->PDADCdelta) {
		ah->PDADCdelta = delta;
		for (i = 1; i < AR9280_TX_GAIN_TABLE_SIZE; i++) {
			regval = ah->originalGain[i] - delta;
			if (regval < 0)
				regval = 0;

			REG_RMW_FIELD(ah,
				      AR_PHY_TX_GAIN_TBL1 + i * 4,
				      AR_PHY_TX_GAIN, regval);
		}
	}
}