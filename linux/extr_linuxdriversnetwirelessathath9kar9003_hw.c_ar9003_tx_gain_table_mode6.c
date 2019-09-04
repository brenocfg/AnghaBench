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
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485_11_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9580 (struct ath_hw*) ; 
 int /*<<< orphan*/  INIT_INI_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9340Modes_low_ob_db_and_spur_tx_gain_table_1p0 ; 
 int /*<<< orphan*/  ar9485Modes_green_spur_ob_db_tx_gain_1_1 ; 
 int /*<<< orphan*/  ar9580_1p0_type6_tx_gain_table ; 

__attribute__((used)) static void ar9003_tx_gain_table_mode6(struct ath_hw *ah)
{
	if (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9340Modes_low_ob_db_and_spur_tx_gain_table_1p0);
	else if (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9485Modes_green_spur_ob_db_tx_gain_1_1);
	else if (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_type6_tx_gain_table);
}