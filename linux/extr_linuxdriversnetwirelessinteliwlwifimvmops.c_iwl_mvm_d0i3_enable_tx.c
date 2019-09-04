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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct iwl_mvm_sta {TYPE_1__* tid_data; } ;
struct iwl_mvm {size_t d0i3_ap_sta_id; int /*<<< orphan*/  d0i3_tx_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  d0i3_exit_waitq; int /*<<< orphan*/  status; int /*<<< orphan*/  d0i3_tx; scalar_t__ d0i3_offloading; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int seq_number; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_mvm*,char*) ; 
 int IWL_MAX_TID_COUNT ; 
 size_t IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_D0I3 ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 scalar_t__ iwl_mvm_tx_skb (struct iwl_mvm*,struct sk_buff*,struct ieee80211_sta*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iwl_mvm_d0i3_enable_tx(struct iwl_mvm *mvm, __le16 *qos_seq)
{
	struct ieee80211_sta *sta = NULL;
	struct iwl_mvm_sta *mvm_ap_sta;
	int i;
	bool wake_queues = false;

	lockdep_assert_held(&mvm->mutex);

	spin_lock_bh(&mvm->d0i3_tx_lock);

	if (mvm->d0i3_ap_sta_id == IWL_MVM_INVALID_STA)
		goto out;

	IWL_DEBUG_RPM(mvm, "re-enqueue packets\n");

	/* get the sta in order to update seq numbers and re-enqueue skbs */
	sta = rcu_dereference_protected(
			mvm->fw_id_to_mac_id[mvm->d0i3_ap_sta_id],
			lockdep_is_held(&mvm->mutex));

	if (IS_ERR_OR_NULL(sta)) {
		sta = NULL;
		goto out;
	}

	if (mvm->d0i3_offloading && qos_seq) {
		/* update qos seq numbers if offloading was enabled */
		mvm_ap_sta = iwl_mvm_sta_from_mac80211(sta);
		for (i = 0; i < IWL_MAX_TID_COUNT; i++) {
			u16 seq = le16_to_cpu(qos_seq[i]);
			/* firmware stores last-used one, we store next one */
			seq += 0x10;
			mvm_ap_sta->tid_data[i].seq_number = seq;
		}
	}
out:
	/* re-enqueue (or drop) all packets */
	while (!skb_queue_empty(&mvm->d0i3_tx)) {
		struct sk_buff *skb = __skb_dequeue(&mvm->d0i3_tx);

		if (!sta || iwl_mvm_tx_skb(mvm, skb, sta))
			ieee80211_free_txskb(mvm->hw, skb);

		/* if the skb_queue is not empty, we need to wake queues */
		wake_queues = true;
	}
	clear_bit(IWL_MVM_STATUS_IN_D0I3, &mvm->status);
	wake_up(&mvm->d0i3_exit_waitq);
	mvm->d0i3_ap_sta_id = IWL_MVM_INVALID_STA;
	if (wake_queues)
		ieee80211_wake_queues(mvm->hw);

	spin_unlock_bh(&mvm->d0i3_tx_lock);
}