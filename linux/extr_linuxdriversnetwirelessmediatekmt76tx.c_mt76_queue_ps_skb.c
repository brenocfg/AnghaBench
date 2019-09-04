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
struct mt76_wcid {int dummy; } ;
struct mt76_queue {int dummy; } ;
struct mt76_dev {TYPE_1__* queue_ops; struct mt76_queue* q_tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; TYPE_2__ control; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tx_queue_skb ) (struct mt76_dev*,struct mt76_queue*,struct sk_buff*,struct mt76_wcid*,struct ieee80211_sta*) ;} ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_CTRL_PS_RESPONSE ; 
 int /*<<< orphan*/  IEEE80211_TX_STATUS_EOSP ; 
 size_t MT_TXQ_PSD ; 
 int /*<<< orphan*/  mt76_skb_set_moredata (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,struct mt76_queue*,struct sk_buff*,struct mt76_wcid*,struct ieee80211_sta*) ; 

__attribute__((used)) static void
mt76_queue_ps_skb(struct mt76_dev *dev, struct ieee80211_sta *sta,
		  struct sk_buff *skb, bool last)
{
	struct mt76_wcid *wcid = (struct mt76_wcid *) sta->drv_priv;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct mt76_queue *hwq = &dev->q_tx[MT_TXQ_PSD];

	info->control.flags |= IEEE80211_TX_CTRL_PS_RESPONSE;
	if (last)
		info->flags |= IEEE80211_TX_STATUS_EOSP;

	mt76_skb_set_moredata(skb, !last);
	dev->queue_ops->tx_queue_skb(dev, hwq, skb, wcid, sta);
}