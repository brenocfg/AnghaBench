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
typedef  size_t u32 ;
struct ath_hw {scalar_t__ PDADCdelta; int /*<<< orphan*/ * originalGain; } ;

/* Variables and functions */
 size_t AR9280_TX_GAIN_TABLE_SIZE ; 
 int /*<<< orphan*/  AR9287_AN_TXPC0 ; 
 int /*<<< orphan*/  AR9287_AN_TXPC0_TXPCMODE ; 
 int /*<<< orphan*/  AR9287_AN_TXPC0_TXPCMODE_S ; 
 int /*<<< orphan*/  AR9287_AN_TXPC0_TXPCMODE_TEMPSENSE ; 
 int /*<<< orphan*/  AR_PHY_TX_GAIN ; 
 scalar_t__ AR_PHY_TX_GAIN_TBL1 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL9 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL9_RES_DC_REMOVAL ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OLC_FOR_AR9280_20_LATER ; 
 scalar_t__ OLC_FOR_AR9287_10_LATER ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_analog_shift_rmw (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ar9002_olc_init(struct ath_hw *ah)
{
	u32 i;

	if (!OLC_FOR_AR9280_20_LATER)
		return;

	if (OLC_FOR_AR9287_10_LATER) {
		REG_SET_BIT(ah, AR_PHY_TX_PWRCTRL9,
				AR_PHY_TX_PWRCTRL9_RES_DC_REMOVAL);
		ath9k_hw_analog_shift_rmw(ah, AR9287_AN_TXPC0,
				AR9287_AN_TXPC0_TXPCMODE,
				AR9287_AN_TXPC0_TXPCMODE_S,
				AR9287_AN_TXPC0_TXPCMODE_TEMPSENSE);
		udelay(100);
	} else {
		for (i = 0; i < AR9280_TX_GAIN_TABLE_SIZE; i++)
			ah->originalGain[i] =
				MS(REG_READ(ah, AR_PHY_TX_GAIN_TBL1 + i * 4),
						AR_PHY_TX_GAIN);
		ah->PDADCdelta = 0;
	}
}