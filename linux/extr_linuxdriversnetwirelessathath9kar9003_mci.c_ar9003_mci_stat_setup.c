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
struct ath9k_hw_mci {int config; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MCI_DBG_CNT_CTRL ; 
 int /*<<< orphan*/  AR_MCI_DBG_CNT_CTRL_BT_LINKID ; 
 int /*<<< orphan*/  AR_MCI_DBG_CNT_CTRL_ENABLE ; 
 int /*<<< orphan*/  AR_SREV_9565 (struct ath_hw*) ; 
 int ATH_MCI_CONFIG_MCI_STAT_DBG ; 
 int MCI_STAT_ALL_BT_LINKID ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar9003_mci_stat_setup(struct ath_hw *ah)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	if (!AR_SREV_9565(ah))
		return;

	if (mci->config & ATH_MCI_CONFIG_MCI_STAT_DBG) {
		REG_RMW_FIELD(ah, AR_MCI_DBG_CNT_CTRL,
			      AR_MCI_DBG_CNT_CTRL_ENABLE, 1);
		REG_RMW_FIELD(ah, AR_MCI_DBG_CNT_CTRL,
			      AR_MCI_DBG_CNT_CTRL_BT_LINKID,
			      MCI_STAT_ALL_BT_LINKID);
	} else {
		REG_RMW_FIELD(ah, AR_MCI_DBG_CNT_CTRL,
			      AR_MCI_DBG_CNT_CTRL_ENABLE, 0);
	}
}