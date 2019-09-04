#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mt76_wcid {int /*<<< orphan*/  tx_rate_set; } ;
struct mt76_queue {int queued; int ndesc; int /*<<< orphan*/  lock; } ;
struct mt76_dev {int /*<<< orphan*/  hw; TYPE_2__* queue_ops; struct mt76_queue* q_tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  rates; int /*<<< orphan*/  vif; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* kick ) (struct mt76_dev*,struct mt76_queue*) ;int /*<<< orphan*/  (* tx_queue_skb ) (struct mt76_dev*,struct mt76_queue*,struct sk_buff*,struct mt76_wcid*,struct ieee80211_sta*) ;} ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int MT_TXQ_BE ; 
 int MT_TXQ_PSD ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_get_tx_rates (int /*<<< orphan*/ ,struct ieee80211_sta*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,int) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,struct mt76_queue*,struct sk_buff*,struct mt76_wcid*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  stub2 (struct mt76_dev*,struct mt76_queue*) ; 

void
mt76_tx(struct mt76_dev *dev, struct ieee80211_sta *sta,
	struct mt76_wcid *wcid, struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct mt76_queue *q;
	int qid = skb_get_queue_mapping(skb);

	if (WARN_ON(qid >= MT_TXQ_PSD)) {
		qid = MT_TXQ_BE;
		skb_set_queue_mapping(skb, qid);
	}

	if (!wcid->tx_rate_set)
		ieee80211_get_tx_rates(info->control.vif, sta, skb,
				       info->control.rates, 1);

	q = &dev->q_tx[qid];

	spin_lock_bh(&q->lock);
	dev->queue_ops->tx_queue_skb(dev, q, skb, wcid, sta);
	dev->queue_ops->kick(dev, q);

	if (q->queued > q->ndesc - 8)
		ieee80211_stop_queue(dev->hw, skb_get_queue_mapping(skb));
	spin_unlock_bh(&q->lock);
}