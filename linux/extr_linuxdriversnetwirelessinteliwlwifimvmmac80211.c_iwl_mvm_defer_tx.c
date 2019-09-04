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
struct iwl_mvm_sta {scalar_t__ sta_id; } ;
struct iwl_mvm {scalar_t__ d0i3_ap_sta_id; int /*<<< orphan*/  d0i3_tx_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  d0i3_tx; int /*<<< orphan*/  status; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 scalar_t__ IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_REF_TX ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_D0I3 ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_ref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool iwl_mvm_defer_tx(struct iwl_mvm *mvm,
			     struct ieee80211_sta *sta,
			     struct sk_buff *skb)
{
	struct iwl_mvm_sta *mvmsta;
	bool defer = false;

	/*
	 * double check the IN_D0I3 flag both before and after
	 * taking the spinlock, in order to prevent taking
	 * the spinlock when not needed.
	 */
	if (likely(!test_bit(IWL_MVM_STATUS_IN_D0I3, &mvm->status)))
		return false;

	spin_lock(&mvm->d0i3_tx_lock);
	/*
	 * testing the flag again ensures the skb dequeue
	 * loop (on d0i3 exit) hasn't run yet.
	 */
	if (!test_bit(IWL_MVM_STATUS_IN_D0I3, &mvm->status))
		goto out;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	if (mvmsta->sta_id == IWL_MVM_INVALID_STA ||
	    mvmsta->sta_id != mvm->d0i3_ap_sta_id)
		goto out;

	__skb_queue_tail(&mvm->d0i3_tx, skb);
	ieee80211_stop_queues(mvm->hw);

	/* trigger wakeup */
	iwl_mvm_ref(mvm, IWL_MVM_REF_TX);
	iwl_mvm_unref(mvm, IWL_MVM_REF_TX);

	defer = true;
out:
	spin_unlock(&mvm->d0i3_tx_lock);
	return defer;
}