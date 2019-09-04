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
struct ath_hw {int /*<<< orphan*/  ini_modes_rxgain_xlna; int /*<<< orphan*/  ini_modes_rxgain_bb_postamble; int /*<<< orphan*/  ini_modes_rxgain_bb_core; int /*<<< orphan*/  iniModesRxGain; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9462_20 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462_21 (struct ath_hw*) ; 
 int /*<<< orphan*/  INIT_INI_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9462_2p0_baseband_core_mix_rxgain ; 
 int /*<<< orphan*/  ar9462_2p0_baseband_postamble_5g_xlna ; 
 int /*<<< orphan*/  ar9462_2p0_baseband_postamble_mix_rxgain ; 
 int /*<<< orphan*/  ar9462_2p0_common_mixed_rx_gain ; 
 int /*<<< orphan*/  ar9462_2p1_baseband_core_mix_rxgain ; 
 int /*<<< orphan*/  ar9462_2p1_baseband_postamble_5g_xlna ; 
 int /*<<< orphan*/  ar9462_2p1_baseband_postamble_mix_rxgain ; 
 int /*<<< orphan*/  ar9462_2p1_common_mixed_rx_gain ; 

__attribute__((used)) static void ar9003_rx_gain_table_mode2(struct ath_hw *ah)
{
	if (AR_SREV_9462_21(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p1_common_mixed_rx_gain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_bb_core,
			       ar9462_2p1_baseband_core_mix_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_bb_postamble,
			       ar9462_2p1_baseband_postamble_mix_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       ar9462_2p1_baseband_postamble_5g_xlna);
	} else if (AR_SREV_9462_20(ah)) {
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p0_common_mixed_rx_gain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_bb_core,
			       ar9462_2p0_baseband_core_mix_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_bb_postamble,
			       ar9462_2p0_baseband_postamble_mix_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       ar9462_2p0_baseband_postamble_5g_xlna);
	}
}