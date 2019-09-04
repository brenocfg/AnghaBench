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
struct mt76x2_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ status; } ;
struct TYPE_3__ {int idx; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_hw (struct mt76x2_dev*) ; 

void mt76x2_tx_complete(struct mt76x2_dev *dev, struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	if (info->flags & IEEE80211_TX_CTL_AMPDU) {
		ieee80211_free_txskb(mt76_hw(dev), skb);
	} else {
		ieee80211_tx_info_clear_status(info);
		info->status.rates[0].idx = -1;
		info->flags |= IEEE80211_TX_STAT_ACK;
		ieee80211_tx_status(mt76_hw(dev), skb);
	}
}