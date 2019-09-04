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
struct iwl_mvm_sta {int disable_tx; int /*<<< orphan*/  lock; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_sta_block_awake (int /*<<< orphan*/ ,struct ieee80211_sta*,int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_sta_modify_disable_tx (struct iwl_mvm*,struct iwl_mvm_sta*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iwl_mvm_sta_modify_disable_tx_ap(struct iwl_mvm *mvm,
				      struct ieee80211_sta *sta,
				      bool disable)
{
	struct iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);

	spin_lock_bh(&mvm_sta->lock);

	if (mvm_sta->disable_tx == disable) {
		spin_unlock_bh(&mvm_sta->lock);
		return;
	}

	mvm_sta->disable_tx = disable;

	/* Tell mac80211 to start/stop queuing tx for this station */
	ieee80211_sta_block_awake(mvm->hw, sta, disable);

	iwl_mvm_sta_modify_disable_tx(mvm, mvm_sta, disable);

	spin_unlock_bh(&mvm_sta->lock);
}