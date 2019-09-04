#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ analog_shiftreg; } ;
struct TYPE_8__ {int ia_rows; } ;
struct ath_hw {int /*<<< orphan*/  iniModesFastClock; int /*<<< orphan*/  iniBB_RfGain; TYPE_2__ config; TYPE_4__ iniCommon; int /*<<< orphan*/  iniModesTxGain; int /*<<< orphan*/  iniModesRxGain; scalar_t__ need_an_top2_fixup; TYPE_4__ iniModes; int /*<<< orphan*/  iniAddac; TYPE_1__* eep_ops; } ;
struct ath_common {TYPE_3__* bus_ops; } ;
struct ath9k_channel {int dummy; } ;
struct TYPE_7__ {scalar_t__ ath_bus_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_addac ) (struct ath_hw*,struct ath9k_channel*) ;} ;

/* Variables and functions */
 int AR_AN_TOP2 ; 
 int AR_AN_TOP2_PWDCLKIND ; 
 int AR_PHY (int /*<<< orphan*/ ) ; 
 int AR_PHY_ADC_SERIAL_CTL ; 
 int /*<<< orphan*/  AR_PHY_RF_CTL3 ; 
 int AR_PHY_SEL_EXTERNAL_RADIO ; 
 int AR_PHY_SEL_INTERNAL_ADDAC ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_ENA ; 
 int /*<<< orphan*/  AR_PHY_TX_END_TO_ADC_ON ; 
 scalar_t__ AR_SREV_9271_10 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285_12_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287_11_OR_LATER (struct ath_hw*) ; 
 scalar_t__ ATH_USB ; 
 int /*<<< orphan*/  DO_DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int INI_RA (TYPE_4__*,int,int) ; 
 scalar_t__ IS_CHAN_5GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_A_FAST_CLOCK (struct ath_hw*,struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  REG_WRITE_ARRAY (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ar5008_hw_init_chain_masks (struct ath_hw*) ; 
 int /*<<< orphan*/  ar5008_hw_override_ini (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar5008_hw_set_channel_regs (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_apply_txpower (struct ath_hw*,struct ath9k_channel*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_rf_regs (struct ath_hw*,struct ath9k_channel*,int) ; 
 int /*<<< orphan*/  ath9k_olc_init (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ar5008_hw_process_ini(struct ath_hw *ah,
				 struct ath9k_channel *chan)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int i, regWrites = 0;
	u32 modesIndex, freqIndex;

	if (IS_CHAN_5GHZ(chan)) {
		freqIndex = 1;
		modesIndex = IS_CHAN_HT40(chan) ? 2 : 1;
	} else {
		freqIndex = 2;
		modesIndex = IS_CHAN_HT40(chan) ? 3 : 4;
	}

	/*
	 * Set correct baseband to analog shift setting to
	 * access analog chips.
	 */
	REG_WRITE(ah, AR_PHY(0), 0x00000007);

	/* Write ADDAC shifts */
	REG_WRITE(ah, AR_PHY_ADC_SERIAL_CTL, AR_PHY_SEL_EXTERNAL_RADIO);
	if (ah->eep_ops->set_addac)
		ah->eep_ops->set_addac(ah, chan);

	REG_WRITE_ARRAY(&ah->iniAddac, 1, regWrites);
	REG_WRITE(ah, AR_PHY_ADC_SERIAL_CTL, AR_PHY_SEL_INTERNAL_ADDAC);

	ENABLE_REGWRITE_BUFFER(ah);

	for (i = 0; i < ah->iniModes.ia_rows; i++) {
		u32 reg = INI_RA(&ah->iniModes, i, 0);
		u32 val = INI_RA(&ah->iniModes, i, modesIndex);

		if (reg == AR_AN_TOP2 && ah->need_an_top2_fixup)
			val &= ~AR_AN_TOP2_PWDCLKIND;

		REG_WRITE(ah, reg, val);

		if (reg >= 0x7800 && reg < 0x78a0
		    && ah->config.analog_shiftreg
		    && (common->bus_ops->ath_bus_type != ATH_USB)) {
			udelay(100);
		}

		DO_DELAY(regWrites);
	}

	REGWRITE_BUFFER_FLUSH(ah);

	if (AR_SREV_9280(ah) || AR_SREV_9287_11_OR_LATER(ah))
		REG_WRITE_ARRAY(&ah->iniModesRxGain, modesIndex, regWrites);

	if (AR_SREV_9280(ah) || AR_SREV_9285_12_OR_LATER(ah) ||
	    AR_SREV_9287_11_OR_LATER(ah))
		REG_WRITE_ARRAY(&ah->iniModesTxGain, modesIndex, regWrites);

	if (AR_SREV_9271_10(ah)) {
		REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN, AR_PHY_SPECTRAL_SCAN_ENA);
		REG_RMW_FIELD(ah, AR_PHY_RF_CTL3, AR_PHY_TX_END_TO_ADC_ON, 0xa);
	}

	ENABLE_REGWRITE_BUFFER(ah);

	/* Write common array parameters */
	for (i = 0; i < ah->iniCommon.ia_rows; i++) {
		u32 reg = INI_RA(&ah->iniCommon, i, 0);
		u32 val = INI_RA(&ah->iniCommon, i, 1);

		REG_WRITE(ah, reg, val);

		if (reg >= 0x7800 && reg < 0x78a0
		    && ah->config.analog_shiftreg
		    && (common->bus_ops->ath_bus_type != ATH_USB)) {
			udelay(100);
		}

		DO_DELAY(regWrites);
	}

	REGWRITE_BUFFER_FLUSH(ah);

	REG_WRITE_ARRAY(&ah->iniBB_RfGain, freqIndex, regWrites);

	if (IS_CHAN_A_FAST_CLOCK(ah, chan))
		REG_WRITE_ARRAY(&ah->iniModesFastClock, modesIndex,
				regWrites);

	ar5008_hw_override_ini(ah, chan);
	ar5008_hw_set_channel_regs(ah, chan);
	ar5008_hw_init_chain_masks(ah);
	ath9k_olc_init(ah);
	ath9k_hw_apply_txpower(ah, chan, false);

	/* Write analog registers */
	if (!ath9k_hw_set_rf_regs(ah, chan, freqIndex)) {
		ath_err(ath9k_hw_common(ah), "ar5416SetRfRegs failed\n");
		return -EIO;
	}

	return 0;
}