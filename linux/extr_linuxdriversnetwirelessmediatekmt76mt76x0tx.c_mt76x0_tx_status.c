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
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;
struct mt76x0_dev {int /*<<< orphan*/  mac_lock; TYPE_3__ mt76; } ;
struct TYPE_5__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; TYPE_2__ status; } ;
struct TYPE_4__ {int idx; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  mt76x0_tx_skb_remove_dma_overhead (struct sk_buff*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mt76x0_tx_status(struct mt76x0_dev *dev, struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	mt76x0_tx_skb_remove_dma_overhead(skb, info);

	ieee80211_tx_info_clear_status(info);
	info->status.rates[0].idx = -1;
	info->flags |= IEEE80211_TX_STAT_ACK;

	spin_lock(&dev->mac_lock);
	ieee80211_tx_status(dev->mt76.hw, skb);
	spin_unlock(&dev->mac_lock);
}