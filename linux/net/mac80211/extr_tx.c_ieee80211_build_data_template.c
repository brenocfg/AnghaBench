#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sta_info {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_tx_data {struct sk_buff* skb; int /*<<< orphan*/  sta; struct ieee80211_sub_if_data* sdata; int /*<<< orphan*/  local; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  local; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 scalar_t__ TX_CONTINUE ; 
 struct sk_buff* ieee80211_build_hdr (struct ieee80211_sub_if_data*,struct sk_buff*,int /*<<< orphan*/ ,struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_lookup_ra_sta (struct ieee80211_sub_if_data*,struct sk_buff*,struct sta_info**) ; 
 scalar_t__ ieee80211_tx_h_select_key (struct ieee80211_tx_data*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

struct sk_buff *
ieee80211_build_data_template(struct ieee80211_sub_if_data *sdata,
			      struct sk_buff *skb, u32 info_flags)
{
	struct ieee80211_hdr *hdr;
	struct ieee80211_tx_data tx = {
		.local = sdata->local,
		.sdata = sdata,
	};
	struct sta_info *sta;

	rcu_read_lock();

	if (ieee80211_lookup_ra_sta(sdata, skb, &sta)) {
		kfree_skb(skb);
		skb = ERR_PTR(-EINVAL);
		goto out;
	}

	skb = ieee80211_build_hdr(sdata, skb, info_flags, sta, 0);
	if (IS_ERR(skb))
		goto out;

	hdr = (void *)skb->data;
	tx.sta = sta_info_get(sdata, hdr->addr1);
	tx.skb = skb;

	if (ieee80211_tx_h_select_key(&tx) != TX_CONTINUE) {
		rcu_read_unlock();
		kfree_skb(skb);
		return ERR_PTR(-EINVAL);
	}

out:
	rcu_read_unlock();
	return skb;
}