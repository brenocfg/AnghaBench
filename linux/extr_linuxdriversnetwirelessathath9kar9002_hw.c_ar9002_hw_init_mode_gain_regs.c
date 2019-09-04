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
typedef  scalar_t__ u32 ;
struct ath_hw {int /*<<< orphan*/  iniModesTxGain; int /*<<< orphan*/  iniModesRxGain; TYPE_1__* eep_ops; } ;
struct TYPE_2__ {scalar_t__ (* get_eeprom ) (struct ath_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ AR5416_EEP_TXGAIN_HIGH_POWER ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285E_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285_12_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287_11_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  EEP_TXGAIN_TYPE ; 
 int /*<<< orphan*/  INIT_INI_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9271_hw_init_txgain_ini (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ar9280_20_hw_init_rxgain_ini (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9280_20_hw_init_txgain_ini (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ar9285Modes_XE2_0_high_power ; 
 int /*<<< orphan*/  ar9285Modes_XE2_0_normal_power ; 
 int /*<<< orphan*/  ar9285Modes_high_power_tx_gain_9285_1_2 ; 
 int /*<<< orphan*/  ar9285Modes_original_tx_gain_9285_1_2 ; 
 int /*<<< orphan*/  ar9287Modes_rx_gain_9287_1_1 ; 
 int /*<<< orphan*/  ar9287Modes_tx_gain_9287_1_1 ; 
 scalar_t__ stub1 (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9002_hw_init_mode_gain_regs(struct ath_hw *ah)
{
	u32 txgain_type = ah->eep_ops->get_eeprom(ah, EEP_TXGAIN_TYPE);

	if (AR_SREV_9287_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9287Modes_rx_gain_9287_1_1);
	else if (AR_SREV_9280_20(ah))
		ar9280_20_hw_init_rxgain_ini(ah);

	if (AR_SREV_9271(ah)) {
		ar9271_hw_init_txgain_ini(ah, txgain_type);
	} else if (AR_SREV_9287_11_OR_LATER(ah)) {
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9287Modes_tx_gain_9287_1_1);
	} else if (AR_SREV_9280_20(ah)) {
		ar9280_20_hw_init_txgain_ini(ah, txgain_type);
	} else if (AR_SREV_9285_12_OR_LATER(ah)) {
		/* txgain table */
		if (txgain_type == AR5416_EEP_TXGAIN_HIGH_POWER) {
			if (AR_SREV_9285E_20(ah)) {
				INIT_INI_ARRAY(&ah->iniModesTxGain,
					       ar9285Modes_XE2_0_high_power);
			} else {
				INIT_INI_ARRAY(&ah->iniModesTxGain,
					ar9285Modes_high_power_tx_gain_9285_1_2);
			}
		} else {
			if (AR_SREV_9285E_20(ah)) {
				INIT_INI_ARRAY(&ah->iniModesTxGain,
					       ar9285Modes_XE2_0_normal_power);
			} else {
				INIT_INI_ARRAY(&ah->iniModesTxGain,
					ar9285Modes_original_tx_gain_9285_1_2);
			}
		}
	}
}