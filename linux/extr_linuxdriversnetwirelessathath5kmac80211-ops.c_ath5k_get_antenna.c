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
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_hw {int ah_ant_mode; } ;

/* Variables and functions */
#define  AR5K_ANTMODE_DEFAULT 130 
#define  AR5K_ANTMODE_FIXED_A 129 
#define  AR5K_ANTMODE_FIXED_B 128 

__attribute__((used)) static int
ath5k_get_antenna(struct ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
{
	struct ath5k_hw *ah = hw->priv;

	switch (ah->ah_ant_mode) {
	case AR5K_ANTMODE_FIXED_A:
		*tx_ant = 1; *rx_ant = 1; break;
	case AR5K_ANTMODE_FIXED_B:
		*tx_ant = 2; *rx_ant = 2; break;
	case AR5K_ANTMODE_DEFAULT:
		*tx_ant = 3; *rx_ant = 3; break;
	}
	return 0;
}