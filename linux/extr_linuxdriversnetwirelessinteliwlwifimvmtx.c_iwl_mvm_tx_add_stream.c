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
typedef  size_t u8 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct iwl_mvm_sta {TYPE_1__* tid_data; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  deferred_traffic_tid_map; int /*<<< orphan*/  lock; } ;
struct iwl_mvm {int /*<<< orphan*/  add_stream_wk; int /*<<< orphan*/  sta_deferred_frames; } ;
struct ieee80211_tx_info {size_t hw_queue; } ;
struct TYPE_2__ {struct sk_buff_head deferred_tx_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  iwl_mvm_stop_mac_queues (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 

__attribute__((used)) static void iwl_mvm_tx_add_stream(struct iwl_mvm *mvm,
				  struct iwl_mvm_sta *mvm_sta, u8 tid,
				  struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 mac_queue = info->hw_queue;
	struct sk_buff_head *deferred_tx_frames;

	lockdep_assert_held(&mvm_sta->lock);

	mvm_sta->deferred_traffic_tid_map |= BIT(tid);
	set_bit(mvm_sta->sta_id, mvm->sta_deferred_frames);

	deferred_tx_frames = &mvm_sta->tid_data[tid].deferred_tx_frames;

	skb_queue_tail(deferred_tx_frames, skb);

	/*
	 * The first deferred frame should've stopped the MAC queues, so we
	 * should never get a second deferred frame for the RA/TID.
	 * In case of GSO the first packet may have been split, so don't warn.
	 */
	if (skb_queue_len(deferred_tx_frames) == 1) {
		iwl_mvm_stop_mac_queues(mvm, BIT(mac_queue));
		schedule_work(&mvm->add_stream_wk);
	}
}