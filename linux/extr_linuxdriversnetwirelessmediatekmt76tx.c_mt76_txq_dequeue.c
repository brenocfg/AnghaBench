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
struct sk_buff {int priority; } ;
struct mt76_txq {int /*<<< orphan*/  retry_q; } ;
struct mt76_dev {int /*<<< orphan*/  hw; } ;
struct ieee80211_txq {int /*<<< orphan*/  sta; } ;

/* Variables and functions */
 int IEEE80211_QOS_CTL_TID_MASK ; 
 int /*<<< orphan*/  ieee80211_sta_set_buffered (int /*<<< orphan*/ ,int,int) ; 
 struct sk_buff* ieee80211_tx_dequeue (int /*<<< orphan*/ ,struct ieee80211_txq*) ; 
 struct ieee80211_txq* mtxq_to_txq (struct mt76_txq*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *
mt76_txq_dequeue(struct mt76_dev *dev, struct mt76_txq *mtxq, bool ps)
{
	struct ieee80211_txq *txq = mtxq_to_txq(mtxq);
	struct sk_buff *skb;

	skb = skb_dequeue(&mtxq->retry_q);
	if (skb) {
		u8 tid = skb->priority & IEEE80211_QOS_CTL_TID_MASK;

		if (ps && skb_queue_empty(&mtxq->retry_q))
			ieee80211_sta_set_buffered(txq->sta, tid, false);

		return skb;
	}

	skb = ieee80211_tx_dequeue(dev->hw, txq);
	if (!skb)
		return NULL;

	return skb;
}