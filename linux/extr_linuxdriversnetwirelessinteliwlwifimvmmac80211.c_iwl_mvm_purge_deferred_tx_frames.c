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
struct sk_buff {int dummy; } ;
struct iwl_mvm_tid_data {int /*<<< orphan*/  deferred_tx_frames; } ;
struct iwl_mvm_sta {int /*<<< orphan*/  lock; struct iwl_mvm_tid_data* tid_data; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  hw_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IWL_MAX_TID_COUNT ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  iwl_mvm_start_mac_queues (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_purge_deferred_tx_frames(struct iwl_mvm *mvm,
					     struct iwl_mvm_sta *mvm_sta)
{
	struct iwl_mvm_tid_data *tid_data;
	struct sk_buff *skb;
	int i;

	spin_lock_bh(&mvm_sta->lock);
	for (i = 0; i <= IWL_MAX_TID_COUNT; i++) {
		tid_data = &mvm_sta->tid_data[i];

		while ((skb = __skb_dequeue(&tid_data->deferred_tx_frames))) {
			struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

			/*
			 * The first deferred frame should've stopped the MAC
			 * queues, so we should never get a second deferred
			 * frame for the RA/TID.
			 */
			iwl_mvm_start_mac_queues(mvm, BIT(info->hw_queue));
			ieee80211_free_txskb(mvm->hw, skb);
		}
	}
	spin_unlock_bh(&mvm_sta->lock);
}