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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vif; } ;
struct ieee80211_tx_info {int hw_queue; TYPE_1__ control; } ;
struct ieee80211_hw {int queues; } ;
struct ieee80211_local {int /*<<< orphan*/  queue_stop_reason_lock; int /*<<< orphan*/ * pending; struct ieee80211_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_QUEUE_STOP_REASON_SKB_ADD ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __ieee80211_stop_queue (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ieee80211_wake_queue (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int,unsigned long*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ieee80211_add_pending_skbs(struct ieee80211_local *local,
				struct sk_buff_head *skbs)
{
	struct ieee80211_hw *hw = &local->hw;
	struct sk_buff *skb;
	unsigned long flags;
	int queue, i;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	while ((skb = skb_dequeue(skbs))) {
		struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		if (WARN_ON(!info->control.vif)) {
			ieee80211_free_txskb(&local->hw, skb);
			continue;
		}

		queue = info->hw_queue;

		__ieee80211_stop_queue(hw, queue,
				IEEE80211_QUEUE_STOP_REASON_SKB_ADD,
				false);

		__skb_queue_tail(&local->pending[queue], skb);
	}

	for (i = 0; i < hw->queues; i++)
		__ieee80211_wake_queue(hw, i,
			IEEE80211_QUEUE_STOP_REASON_SKB_ADD,
			false, &flags);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
}