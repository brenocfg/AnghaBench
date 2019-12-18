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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {scalar_t__ len; scalar_t__ ip_summed; struct sta_info* next; int /*<<< orphan*/ * prev; int /*<<< orphan*/  fast_tx; int /*<<< orphan*/  sk; } ;
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; struct sk_buff* next; int /*<<< orphan*/ * prev; int /*<<< orphan*/  fast_tx; int /*<<< orphan*/  sk; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_sk_pacing_shift; } ;
struct ieee80211_local {TYPE_2__ hw; TYPE_1__* ops; } ;
struct ieee80211_fast_tx {int dummy; } ;
struct TYPE_3__ {scalar_t__ wake_tx_queue; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ ETH_HLEN ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 scalar_t__ IS_ERR (struct sta_info*) ; 
 int /*<<< orphan*/  __ieee80211_select_queue (struct ieee80211_sub_if_data*,struct sta_info*,struct sta_info*) ; 
 int /*<<< orphan*/  consume_skb (struct sta_info*) ; 
 struct sta_info* ieee80211_build_hdr (struct ieee80211_sub_if_data*,struct sta_info*,int /*<<< orphan*/ ,struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_lookup_ra_sta (struct ieee80211_sub_if_data*,struct sta_info*,struct sta_info**) ; 
 int /*<<< orphan*/  ieee80211_tx_stats (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_xmit (struct ieee80211_sub_if_data*,struct sta_info*,struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_xmit_fast (struct ieee80211_sub_if_data*,struct sta_info*,struct ieee80211_fast_tx*,struct sta_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sta_info*) ; 
 struct ieee80211_fast_tx* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_pacing_shift_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_checksum_help (struct sta_info*) ; 
 int /*<<< orphan*/  skb_checksum_start_offset (struct sta_info*) ; 
 struct sta_info* skb_gso_segment (struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sta_info*) ; 
 scalar_t__ skb_linearize (struct sta_info*) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void __ieee80211_subif_start_xmit(struct sk_buff *skb,
				  struct net_device *dev,
				  u32 info_flags,
				  u32 ctrl_flags)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	struct sk_buff *next;

	if (unlikely(skb->len < ETH_HLEN)) {
		kfree_skb(skb);
		return;
	}

	rcu_read_lock();

	if (ieee80211_lookup_ra_sta(sdata, skb, &sta))
		goto out_free;

	if (IS_ERR(sta))
		sta = NULL;

	if (local->ops->wake_tx_queue) {
		u16 queue = __ieee80211_select_queue(sdata, sta, skb);
		skb_set_queue_mapping(skb, queue);
	}

	if (sta) {
		struct ieee80211_fast_tx *fast_tx;

		sk_pacing_shift_update(skb->sk, sdata->local->hw.tx_sk_pacing_shift);

		fast_tx = rcu_dereference(sta->fast_tx);

		if (fast_tx &&
		    ieee80211_xmit_fast(sdata, sta, fast_tx, skb))
			goto out;
	}

	if (skb_is_gso(skb)) {
		struct sk_buff *segs;

		segs = skb_gso_segment(skb, 0);
		if (IS_ERR(segs)) {
			goto out_free;
		} else if (segs) {
			consume_skb(skb);
			skb = segs;
		}
	} else {
		/* we cannot process non-linear frames on this path */
		if (skb_linearize(skb)) {
			kfree_skb(skb);
			goto out;
		}

		/* the frame could be fragmented, software-encrypted, and other
		 * things so we cannot really handle checksum offload with it -
		 * fix it up in software before we handle anything else.
		 */
		if (skb->ip_summed == CHECKSUM_PARTIAL) {
			skb_set_transport_header(skb,
						 skb_checksum_start_offset(skb));
			if (skb_checksum_help(skb))
				goto out_free;
		}
	}

	next = skb;
	while (next) {
		skb = next;
		next = skb->next;

		skb->prev = NULL;
		skb->next = NULL;

		skb = ieee80211_build_hdr(sdata, skb, info_flags,
					  sta, ctrl_flags);
		if (IS_ERR(skb))
			goto out;

		ieee80211_tx_stats(dev, skb->len);

		ieee80211_xmit(sdata, sta, skb, 0);
	}
	goto out;
 out_free:
	kfree_skb(skb);
 out:
	rcu_read_unlock();
}