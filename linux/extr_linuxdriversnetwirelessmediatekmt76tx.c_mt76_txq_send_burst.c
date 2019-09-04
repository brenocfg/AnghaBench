#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mt76_wcid {int /*<<< orphan*/  tx_rate_set; } ;
struct mt76_txq {int /*<<< orphan*/  retry_q; struct mt76_wcid* wcid; } ;
struct mt76_queue {TYPE_2__* entry; int /*<<< orphan*/  swq_queued; } ;
struct mt76_dev {TYPE_3__* queue_ops; int /*<<< orphan*/  state; } ;
struct ieee80211_txq {int /*<<< orphan*/  sta; int /*<<< orphan*/  vif; } ;
struct ieee80211_tx_rate {int dummy; } ;
struct TYPE_4__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct TYPE_6__ {int (* tx_queue_skb ) (struct mt76_dev*,struct mt76_queue*,struct sk_buff*,struct mt76_wcid*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* kick ) (struct mt76_dev*,struct mt76_queue*) ;} ;
struct TYPE_5__ {int schedule; } ;

/* Variables and functions */
 int EBUSY ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int /*<<< orphan*/  MT76_OFFCHANNEL ; 
 int /*<<< orphan*/  MT76_RESET ; 
 int /*<<< orphan*/  ieee80211_get_tx_rates (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct ieee80211_tx_rate*,int) ; 
 int /*<<< orphan*/  mt76_check_agg_ssn (struct mt76_txq*,struct sk_buff*) ; 
 struct sk_buff* mt76_txq_dequeue (struct mt76_dev*,struct mt76_txq*,int) ; 
 struct ieee80211_txq* mtxq_to_txq (struct mt76_txq*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int stub1 (struct mt76_dev*,struct mt76_queue*,struct sk_buff*,struct mt76_wcid*,int /*<<< orphan*/ ) ; 
 int stub2 (struct mt76_dev*,struct mt76_queue*,struct sk_buff*,struct mt76_wcid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mt76_dev*,struct mt76_queue*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76_txq_send_burst(struct mt76_dev *dev, struct mt76_queue *hwq,
		    struct mt76_txq *mtxq, bool *empty)
{
	struct ieee80211_txq *txq = mtxq_to_txq(mtxq);
	struct ieee80211_tx_info *info;
	struct mt76_wcid *wcid = mtxq->wcid;
	struct sk_buff *skb;
	int n_frames = 1, limit;
	struct ieee80211_tx_rate tx_rate;
	bool ampdu;
	bool probe;
	int idx;

	skb = mt76_txq_dequeue(dev, mtxq, false);
	if (!skb) {
		*empty = true;
		return 0;
	}

	info = IEEE80211_SKB_CB(skb);
	if (!wcid->tx_rate_set)
		ieee80211_get_tx_rates(txq->vif, txq->sta, skb,
				       info->control.rates, 1);
	tx_rate = info->control.rates[0];

	probe = (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE);
	ampdu = IEEE80211_SKB_CB(skb)->flags & IEEE80211_TX_CTL_AMPDU;
	limit = ampdu ? 16 : 3;

	if (ampdu)
		mt76_check_agg_ssn(mtxq, skb);

	idx = dev->queue_ops->tx_queue_skb(dev, hwq, skb, wcid, txq->sta);

	if (idx < 0)
		return idx;

	do {
		bool cur_ampdu;

		if (probe)
			break;

		if (test_bit(MT76_OFFCHANNEL, &dev->state) ||
		    test_bit(MT76_RESET, &dev->state))
			return -EBUSY;

		skb = mt76_txq_dequeue(dev, mtxq, false);
		if (!skb) {
			*empty = true;
			break;
		}

		info = IEEE80211_SKB_CB(skb);
		cur_ampdu = info->flags & IEEE80211_TX_CTL_AMPDU;

		if (ampdu != cur_ampdu ||
		    (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)) {
			skb_queue_tail(&mtxq->retry_q, skb);
			break;
		}

		info->control.rates[0] = tx_rate;

		if (cur_ampdu)
			mt76_check_agg_ssn(mtxq, skb);

		idx = dev->queue_ops->tx_queue_skb(dev, hwq, skb, wcid,
						   txq->sta);
		if (idx < 0)
			return idx;

		n_frames++;
	} while (n_frames < limit);

	if (!probe) {
		hwq->swq_queued++;
		hwq->entry[idx].schedule = true;
	}

	dev->queue_ops->kick(dev, hwq);

	return n_frames;
}