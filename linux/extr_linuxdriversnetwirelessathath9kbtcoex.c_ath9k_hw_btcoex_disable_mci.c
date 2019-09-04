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
struct ath_btcoex_hw {int /*<<< orphan*/ * wlan_weight; } ;
struct ath_hw {struct ath_btcoex_hw btcoex_hw; } ;

/* Variables and functions */
 int AR9300_NUM_BT_WEIGHTS ; 
 int /*<<< orphan*/  AR_MCI_COEX_WL_WEIGHTS (int) ; 
 int /*<<< orphan*/  ATH_BTCOEX_STOMP_NONE ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_btcoex_bt_stomp (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_hw_btcoex_disable_mci(struct ath_hw *ah)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	int i;

	ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_NONE);

	for (i = 0; i < AR9300_NUM_BT_WEIGHTS; i++)
		REG_WRITE(ah, AR_MCI_COEX_WL_WEIGHTS(i),
			  btcoex_hw->wlan_weight[i]);
}