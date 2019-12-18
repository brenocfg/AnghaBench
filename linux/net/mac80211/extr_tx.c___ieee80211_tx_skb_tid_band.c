#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int priority; int /*<<< orphan*/  dev; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {int band; } ;

/* Variables and functions */
 TYPE_1__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int ieee80211_ac_from_tid (int) ; 
 int /*<<< orphan*/  ieee80211_xmit (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int) ; 

void __ieee80211_tx_skb_tid_band(struct ieee80211_sub_if_data *sdata,
				 struct sk_buff *skb, int tid,
				 enum nl80211_band band, u32 txdata_flags)
{
	int ac = ieee80211_ac_from_tid(tid);

	skb_reset_mac_header(skb);
	skb_set_queue_mapping(skb, ac);
	skb->priority = tid;

	skb->dev = sdata->dev;

	/*
	 * The other path calling ieee80211_xmit is from the tasklet,
	 * and while we can handle concurrent transmissions locking
	 * requirements are that we do not come into tx with bhs on.
	 */
	local_bh_disable();
	IEEE80211_SKB_CB(skb)->band = band;
	ieee80211_xmit(sdata, NULL, skb, txdata_flags);
	local_bh_enable();
}