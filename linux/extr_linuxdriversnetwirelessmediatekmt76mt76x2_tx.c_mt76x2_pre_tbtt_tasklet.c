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
struct mt76x2_vif {int /*<<< orphan*/  group_wcid; } ;
struct TYPE_4__ {struct mt76_queue* q_tx; } ;
struct mt76x2_dev {TYPE_2__ mt76; int /*<<< orphan*/  q; int /*<<< orphan*/ * tail; struct mt76x2_dev* dev; } ;
struct mt76_queue {int /*<<< orphan*/  lock; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_3__ {struct ieee80211_vif* vif; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct beacon_bc_data {TYPE_2__ mt76; int /*<<< orphan*/  q; int /*<<< orphan*/ * tail; struct beacon_bc_data* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 size_t MT_TXQ_PSD ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76_dma_tx_queue_skb (TYPE_2__*,struct mt76_queue*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_hw (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76_skb_set_moredata (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x2_add_buffered_bc ; 
 int /*<<< orphan*/  mt76x2_resync_beacon_timer (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_update_beacon_iter ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mt76x2_pre_tbtt_tasklet(unsigned long arg)
{
	struct mt76x2_dev *dev = (struct mt76x2_dev *) arg;
	struct mt76_queue *q = &dev->mt76.q_tx[MT_TXQ_PSD];
	struct beacon_bc_data data = {};
	struct sk_buff *skb;
	int i, nframes;

	mt76x2_resync_beacon_timer(dev);

	data.dev = dev;
	__skb_queue_head_init(&data.q);

	ieee80211_iterate_active_interfaces_atomic(mt76_hw(dev),
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt76x2_update_beacon_iter, dev);

	do {
		nframes = skb_queue_len(&data.q);
		ieee80211_iterate_active_interfaces_atomic(mt76_hw(dev),
			IEEE80211_IFACE_ITER_RESUME_ALL,
			mt76x2_add_buffered_bc, &data);
	} while (nframes != skb_queue_len(&data.q));

	if (!nframes)
		return;

	for (i = 0; i < ARRAY_SIZE(data.tail); i++) {
		if (!data.tail[i])
			continue;

		mt76_skb_set_moredata(data.tail[i], false);
	}

	spin_lock_bh(&q->lock);
	while ((skb = __skb_dequeue(&data.q)) != NULL) {
		struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		struct ieee80211_vif *vif = info->control.vif;
		struct mt76x2_vif *mvif = (struct mt76x2_vif *) vif->drv_priv;

		mt76_dma_tx_queue_skb(&dev->mt76, q, skb, &mvif->group_wcid,
				      NULL);
	}
	spin_unlock_bh(&q->lock);
}