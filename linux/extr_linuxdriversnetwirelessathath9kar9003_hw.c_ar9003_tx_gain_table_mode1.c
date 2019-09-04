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
struct ath_hw {int /*<<< orphan*/  iniModesTxGain; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9330_11 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330_12 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462_21 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485_11_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9531 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9531_11 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9531_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9561 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565_11 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9580 (struct ath_hw*) ; 
 int /*<<< orphan*/  INIT_INI_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300Modes_high_ob_db_tx_gain_table_2p2 ; 
 int /*<<< orphan*/  ar9331_modes_high_ob_db_tx_gain_1p1 ; 
 int /*<<< orphan*/  ar9331_modes_high_ob_db_tx_gain_1p2 ; 
 int /*<<< orphan*/  ar9340Modes_high_ob_db_tx_gain_table_1p0 ; 
 int /*<<< orphan*/  ar9462_2p0_modes_high_ob_db_tx_gain ; 
 int /*<<< orphan*/  ar9462_2p1_modes_high_ob_db_tx_gain ; 
 int /*<<< orphan*/  ar9485Modes_high_ob_db_tx_gain_1_1 ; 
 int /*<<< orphan*/  ar955x_1p0_modes_no_xpa_tx_gain_table ; 
 int /*<<< orphan*/  ar9565_1p0_modes_high_ob_db_tx_gain_table ; 
 int /*<<< orphan*/  ar9565_1p1_modes_high_ob_db_tx_gain_table ; 
 int /*<<< orphan*/  ar9580_1p0_high_ob_db_tx_gain_table ; 
 int /*<<< orphan*/  qca953x_1p0_modes_no_xpa_tx_gain_table ; 
 int /*<<< orphan*/  qca953x_1p1_modes_no_xpa_tx_gain_table ; 
 int /*<<< orphan*/  qca953x_2p0_modes_no_xpa_tx_gain_table ; 
 int /*<<< orphan*/  qca956x_1p0_modes_no_xpa_tx_gain_table ; 

__attribute__((used)) static void ar9003_tx_gain_table_mode1(struct ath_hw *ah)
{
	if (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_high_ob_db_tx_gain_1p2);
	else if (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_high_ob_db_tx_gain_1p1);
	else if (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9340Modes_high_ob_db_tx_gain_table_1p0);
	else if (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9485Modes_high_ob_db_tx_gain_1_1);
	else if (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_high_ob_db_tx_gain_table);
	else if (AR_SREV_9550(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar955x_1p0_modes_no_xpa_tx_gain_table);
	else if (AR_SREV_9531(ah)) {
		if (AR_SREV_9531_20(ah))
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_2p0_modes_no_xpa_tx_gain_table);
		else if (AR_SREV_9531_11(ah))
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_1p1_modes_no_xpa_tx_gain_table);
		else
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_1p0_modes_no_xpa_tx_gain_table);
	} else if (AR_SREV_9561(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_tx_gain_table);
	else if (AR_SREV_9462_21(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9462_2p1_modes_high_ob_db_tx_gain);
	else if (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9462_2p0_modes_high_ob_db_tx_gain);
	else if (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p1_modes_high_ob_db_tx_gain_table);
	else if (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p0_modes_high_ob_db_tx_gain_table);
	else
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9300Modes_high_ob_db_tx_gain_table_2p2);
}