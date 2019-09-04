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
struct sta_info {int /*<<< orphan*/  fast_tx; } ;
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; struct sk_buff* next; int /*<<< orphan*/ * prev; int /*<<< orphan*/  sk; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_fast_tx {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ ETH_HLEN ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct sta_info*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct sk_buff* ieee80211_build_hdr (struct ieee80211_sub_if_data*,struct sk_buff*,int /*<<< orphan*/ ,struct sta_info*) ; 
 scalar_t__ ieee80211_lookup_ra_sta (struct ieee80211_sub_if_data*,struct sk_buff*,struct sta_info**) ; 
 int /*<<< orphan*/  ieee80211_tx_stats (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_xmit (struct ieee80211_sub_if_data*,struct sta_info*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_xmit_fast (struct ieee80211_sub_if_data*,struct sta_info*,struct ieee80211_fast_tx*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ieee80211_fast_tx* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_pacing_shift_update (int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_checksum_help (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum_start_offset (struct sk_buff*) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void __ieee80211_subif_start_xmit(struct sk_buff *skb,
				  struct net_device *dev,
				  u32 info_flags)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct sta_info *sta;
	struct sk_buff *next;

	if (unlikely(skb->len < ETH_HLEN)) {
		kfree_skb(skb);
		return;
	}

	rcu_read_lock();

	if (ieee80211_lookup_ra_sta(sdata, skb, &sta))
		goto out_free;

	if (!IS_ERR_OR_NULL(sta)) {
		struct ieee80211_fast_tx *fast_tx;

		/* We need a bit of data queued to build aggregates properly, so
		 * instruct the TCP stack to allow more than a single ms of data
		 * to be queued in the stack. The value is a bit-shift of 1
		 * second, so 7 is ~8ms of queued data. Only affects local TCP
		 * sockets.
		 */
		sk_pacing_shift_update(skb->sk, 7);

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

		skb = ieee80211_build_hdr(sdata, skb, info_flags, sta);
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