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
typedef  int u8 ;
typedef  int u32 ;
struct ath9k_hw_mci {scalar_t__ stomp_ftp; int /*<<< orphan*/  concur_tx; } ;
struct ath_btcoex_hw {int* tx_prio; int bt_coex_weights; int* wlan_weight; int /*<<< orphan*/ * bt_weight; struct ath9k_hw_mci mci; } ;
struct ath_hw {struct ath_btcoex_hw btcoex_hw; } ;
typedef  enum ath_stomp_type { ____Placeholder_ath_stomp_type } ath_stomp_type ;

/* Variables and functions */
 int /*<<< orphan*/  AR9300_BT_WGHT ; 
 int AR9300_NUM_WLAN_WEIGHTS ; 
 int /*<<< orphan*/  AR_BTCOEX_BT_WGHT ; 
 int /*<<< orphan*/  AR_BTCOEX_WL_WGHT ; 
 int /*<<< orphan*/  AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int ATH_BTCOEX_STOMP_LOW ; 
 int ATH_BTCOEX_STOMP_LOW_FTP ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int** ar9003_wlan_weights ; 
 int** mci_wlan_weights ; 

void ath9k_hw_btcoex_set_weight(struct ath_hw *ah,
				u32 bt_weight,
				u32 wlan_weight,
				enum ath_stomp_type stomp_type)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u8 txprio_shift[] = { 24, 16, 16, 0 }; /* tx priority weight */
	bool concur_tx = (mci_hw->concur_tx && btcoex_hw->tx_prio[stomp_type]);
	const u32 *weight = ar9003_wlan_weights[stomp_type];
	int i;

	if (!AR_SREV_9300_20_OR_LATER(ah)) {
		btcoex_hw->bt_coex_weights =
			SM(bt_weight, AR_BTCOEX_BT_WGHT) |
			SM(wlan_weight, AR_BTCOEX_WL_WGHT);
		return;
	}

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		enum ath_stomp_type stype =
			((stomp_type == ATH_BTCOEX_STOMP_LOW) &&
			 btcoex_hw->mci.stomp_ftp) ?
			ATH_BTCOEX_STOMP_LOW_FTP : stomp_type;
		weight = mci_wlan_weights[stype];
	}

	for (i = 0; i < AR9300_NUM_WLAN_WEIGHTS; i++) {
		btcoex_hw->bt_weight[i] = AR9300_BT_WGHT;
		btcoex_hw->wlan_weight[i] = weight[i];
		if (concur_tx && i) {
			btcoex_hw->wlan_weight[i] &=
				~(0xff << txprio_shift[i-1]);
			btcoex_hw->wlan_weight[i] |=
				(btcoex_hw->tx_prio[stomp_type] <<
				 txprio_shift[i-1]);
		}
	}

	/* Last WLAN weight has to be adjusted wrt tx priority */
	if (concur_tx) {
		btcoex_hw->wlan_weight[i-1] &= ~(0xff << txprio_shift[i-1]);
		btcoex_hw->wlan_weight[i-1] |= (btcoex_hw->tx_prio[stomp_type]
						      << txprio_shift[i-1]);
	}
}