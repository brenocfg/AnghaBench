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
struct ath_hw {int /*<<< orphan*/  iniModesRxGain; int /*<<< orphan*/  ini_modes_rxgain_xlna; int /*<<< orphan*/  ini_modes_rx_gain_bounds; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9330_11 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330_12 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462_21 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485_11_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9531 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9561 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565_11 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9580 (struct ath_hw*) ; 
 int /*<<< orphan*/  INIT_INI_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300Common_rx_gain_table_2p2 ; 
 int /*<<< orphan*/  ar9331_common_rx_gain_1p1 ; 
 int /*<<< orphan*/  ar9331_common_rx_gain_1p2 ; 
 int /*<<< orphan*/  ar9340Common_rx_gain_table_1p0 ; 
 int /*<<< orphan*/  ar9462_2p0_common_rx_gain ; 
 int /*<<< orphan*/  ar9462_2p1_common_rx_gain ; 
 int /*<<< orphan*/  ar9485_common_rx_gain_1_1 ; 
 int /*<<< orphan*/  ar955x_1p0_common_rx_gain_bounds ; 
 int /*<<< orphan*/  ar955x_1p0_common_rx_gain_table ; 
 int /*<<< orphan*/  ar9565_1p0_Common_rx_gain_table ; 
 int /*<<< orphan*/  ar9565_1p1_Common_rx_gain_table ; 
 int /*<<< orphan*/  ar9580_1p0_rx_gain_table ; 
 int /*<<< orphan*/  qca953x_1p0_common_rx_gain_bounds ; 
 int /*<<< orphan*/  qca953x_1p0_common_rx_gain_table ; 
 int /*<<< orphan*/  qca956x_1p0_common_rx_gain_bounds ; 
 int /*<<< orphan*/  qca956x_1p0_common_rx_gain_table ; 
 int /*<<< orphan*/  qca956x_1p0_xlna_only ; 

__attribute__((used)) static void ar9003_rx_gain_table_mode0(struct ath_hw *ah)
{
	if (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9331_common_rx_gain_1p2);
	else if (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9331_common_rx_gain_1p1);
	else if (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9340Common_rx_gain_table_1p0);
	else if (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9485_common_rx_gain_1_1);
	else if (AR_SREV_9550(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar955x_1p0_common_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
				ar955x_1p0_common_rx_gain_bounds);
	} else if (AR_SREV_9531(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca953x_1p0_common_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca953x_1p0_common_rx_gain_bounds);
	} else if (AR_SREV_9561(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca956x_1p0_common_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca956x_1p0_common_rx_gain_bounds);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       qca956x_1p0_xlna_only);
	} else if (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9580_1p0_rx_gain_table);
	else if (AR_SREV_9462_21(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9462_2p1_common_rx_gain);
	else if (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9462_2p0_common_rx_gain);
	else if (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p1_Common_rx_gain_table);
	else if (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p0_Common_rx_gain_table);
	else
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9300Common_rx_gain_table_2p2);
}