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
struct sk_buff {int len; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;
struct mt76x0_dev {TYPE_3__ mt76; struct mt76_wcid* mon_wcid; } ;
struct mt76_wcid {int hw_key_idx; } ;
struct mt76_vif {struct mt76_wcid group_wcid; } ;
struct mt76_txwi {int dummy; } ;
struct mt76_sta {struct mt76_wcid wcid; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw_key; struct ieee80211_vif* vif; } ;
struct TYPE_4__ {void** status_driver_data; } ;
struct ieee80211_tx_info {TYPE_2__ control; TYPE_1__ status; } ;
struct ieee80211_tx_control {struct ieee80211_sta* sta; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ mt76x0_dma_enqueue_tx (struct mt76x0_dev*,struct sk_buff*,struct mt76_wcid*,int) ; 
 scalar_t__ mt76x0_insert_hdr_pad (struct sk_buff*) ; 
 struct mt76_txwi* mt76x0_push_txwi (struct mt76x0_dev*,struct sk_buff*,struct ieee80211_sta*,struct mt76_wcid*,int) ; 
 scalar_t__ mt76x0_skb_rooms (struct mt76x0_dev*,struct sk_buff*) ; 
 int skb2q (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_mt76x0_tx (TYPE_3__*,struct sk_buff*,struct mt76_sta*,struct mt76_txwi*) ; 

void mt76x0_tx(struct ieee80211_hw *hw, struct ieee80211_tx_control *control,
		struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct mt76x0_dev *dev = hw->priv;
	struct ieee80211_vif *vif = info->control.vif;
	struct ieee80211_sta *sta = control->sta;
	struct mt76_sta *msta = NULL;
	struct mt76_wcid *wcid = dev->mon_wcid;
	struct mt76_txwi *txwi;
	int pkt_len = skb->len;
	int hw_q = skb2q(skb);

	BUILD_BUG_ON(ARRAY_SIZE(info->status.status_driver_data) < 1);
	info->status.status_driver_data[0] = (void *)(unsigned long)pkt_len;

	if (mt76x0_skb_rooms(dev, skb) || mt76x0_insert_hdr_pad(skb)) {
		ieee80211_free_txskb(dev->mt76.hw, skb);
		return;
	}

	if (sta) {
		msta = (struct mt76_sta *) sta->drv_priv;
		wcid = &msta->wcid;
	} else if (vif && (!info->control.hw_key && wcid->hw_key_idx != -1)) {
		struct mt76_vif *mvif = (struct mt76_vif *)vif->drv_priv;

		wcid = &mvif->group_wcid;
	}

	txwi = mt76x0_push_txwi(dev, skb, sta, wcid, pkt_len);

	if (mt76x0_dma_enqueue_tx(dev, skb, wcid, hw_q))
		return;

	trace_mt76x0_tx(&dev->mt76, skb, msta, txwi);
}