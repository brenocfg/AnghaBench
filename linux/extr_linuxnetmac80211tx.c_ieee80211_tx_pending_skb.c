#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sta_info {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  vif; } ;
struct ieee80211_tx_info {int flags; int /*<<< orphan*/  band; TYPE_1__ control; } ;
struct TYPE_6__ {int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;
struct ieee80211_local {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;
struct TYPE_8__ {TYPE_3__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_4__ def; } ;
struct TYPE_7__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_INTFL_NEED_TXPROCESSING ; 
 int __ieee80211_tx (struct ieee80211_local*,struct sk_buff_head*,int /*<<< orphan*/ ,struct sta_info*,int) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int ieee80211_tx (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ieee80211_tx_pending_skb(struct ieee80211_local *local,
				     struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_sub_if_data *sdata;
	struct sta_info *sta;
	struct ieee80211_hdr *hdr;
	bool result;
	struct ieee80211_chanctx_conf *chanctx_conf;

	sdata = vif_to_sdata(info->control.vif);

	if (info->flags & IEEE80211_TX_INTFL_NEED_TXPROCESSING) {
		chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
		if (unlikely(!chanctx_conf)) {
			dev_kfree_skb(skb);
			return true;
		}
		info->band = chanctx_conf->def.chan->band;
		result = ieee80211_tx(sdata, NULL, skb, true, 0);
	} else {
		struct sk_buff_head skbs;

		__skb_queue_head_init(&skbs);
		__skb_queue_tail(&skbs, skb);

		hdr = (struct ieee80211_hdr *)skb->data;
		sta = sta_info_get(sdata, hdr->addr1);

		result = __ieee80211_tx(local, &skbs, skb->len, sta, true);
	}

	return result;
}