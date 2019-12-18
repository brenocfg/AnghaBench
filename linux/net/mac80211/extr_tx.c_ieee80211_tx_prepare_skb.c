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
struct ieee80211_vif {int /*<<< orphan*/ * hw_queue; } ;
struct TYPE_3__ {struct ieee80211_vif* vif; } ;
struct ieee80211_tx_info {int band; int /*<<< orphan*/  hw_queue; TYPE_1__ control; } ;
struct ieee80211_tx_data {int /*<<< orphan*/  skbs; TYPE_2__* sta; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {struct ieee80211_sta sta; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 scalar_t__ TX_DROP ; 
 scalar_t__ WARN_ON (int) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_purge_tx_queue (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_tx_prepare (struct ieee80211_sub_if_data*,struct ieee80211_tx_data*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ invoke_tx_handlers (struct ieee80211_tx_data*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

bool ieee80211_tx_prepare_skb(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif, struct sk_buff *skb,
			      int band, struct ieee80211_sta **sta)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_data tx;
	struct sk_buff *skb2;

	if (ieee80211_tx_prepare(sdata, &tx, NULL, skb) == TX_DROP)
		return false;

	info->band = band;
	info->control.vif = vif;
	info->hw_queue = vif->hw_queue[skb_get_queue_mapping(skb)];

	if (invoke_tx_handlers(&tx))
		return false;

	if (sta) {
		if (tx.sta)
			*sta = &tx.sta->sta;
		else
			*sta = NULL;
	}

	/* this function isn't suitable for fragmented data frames */
	skb2 = __skb_dequeue(&tx.skbs);
	if (WARN_ON(skb2 != skb || !skb_queue_empty(&tx.skbs))) {
		ieee80211_free_txskb(hw, skb2);
		ieee80211_purge_tx_queue(hw, &tx.skbs);
		return false;
	}

	return true;
}