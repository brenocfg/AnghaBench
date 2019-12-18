#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int dummy; } ;
struct sk_buff {int priority; int /*<<< orphan*/  protocol; int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  sta; } ;
struct TYPE_10__ {TYPE_4__ vlan; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {int flags; TYPE_5__ u; TYPE_3__ vif; struct net_device* dev; } ;
struct ieee80211_rx_data {size_t seqno_idx; TYPE_2__* sta; struct sk_buff* skb; struct ieee80211_sub_if_data* sdata; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct TYPE_6__ {int /*<<< orphan*/  syncp; int /*<<< orphan*/ * msdu; } ;
struct TYPE_7__ {TYPE_1__ rx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_802_3 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IEEE80211_SDATA_DONT_BRIDGE_PACKETS ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_deliver_skb_to_local_stack (struct sk_buff*,struct ieee80211_rx_data*) ; 
 int /*<<< orphan*/  ieee80211_rx_stats (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_vif_get_num_mcast_if (struct ieee80211_sub_if_data*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 size_t skb_headlen (struct sk_buff*) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,size_t) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ieee80211_deliver_skb(struct ieee80211_rx_data *rx)
{
	struct ieee80211_sub_if_data *sdata = rx->sdata;
	struct net_device *dev = sdata->dev;
	struct sk_buff *skb, *xmit_skb;
	struct ethhdr *ehdr = (struct ethhdr *) rx->skb->data;
	struct sta_info *dsta;

	skb = rx->skb;
	xmit_skb = NULL;

	ieee80211_rx_stats(dev, skb->len);

	if (rx->sta) {
		/* The seqno index has the same property as needed
		 * for the rx_msdu field, i.e. it is IEEE80211_NUM_TIDS
		 * for non-QoS-data frames. Here we know it's a data
		 * frame, so count MSDUs.
		 */
		u64_stats_update_begin(&rx->sta->rx_stats.syncp);
		rx->sta->rx_stats.msdu[rx->seqno_idx]++;
		u64_stats_update_end(&rx->sta->rx_stats.syncp);
	}

	if ((sdata->vif.type == NL80211_IFTYPE_AP ||
	     sdata->vif.type == NL80211_IFTYPE_AP_VLAN) &&
	    !(sdata->flags & IEEE80211_SDATA_DONT_BRIDGE_PACKETS) &&
	    (sdata->vif.type != NL80211_IFTYPE_AP_VLAN || !sdata->u.vlan.sta)) {
		if (is_multicast_ether_addr(ehdr->h_dest) &&
		    ieee80211_vif_get_num_mcast_if(sdata) != 0) {
			/*
			 * send multicast frames both to higher layers in
			 * local net stack and back to the wireless medium
			 */
			xmit_skb = skb_copy(skb, GFP_ATOMIC);
			if (!xmit_skb)
				net_info_ratelimited("%s: failed to clone multicast frame\n",
						    dev->name);
		} else if (!is_multicast_ether_addr(ehdr->h_dest) &&
			   !ether_addr_equal(ehdr->h_dest, ehdr->h_source)) {
			dsta = sta_info_get(sdata, ehdr->h_dest);
			if (dsta) {
				/*
				 * The destination station is associated to
				 * this AP (in this VLAN), so send the frame
				 * directly to it and do not pass it to local
				 * net stack.
				 */
				xmit_skb = skb;
				skb = NULL;
			}
		}
	}

#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (skb) {
		/* 'align' will only take the values 0 or 2 here since all
		 * frames are required to be aligned to 2-byte boundaries
		 * when being passed to mac80211; the code here works just
		 * as well if that isn't true, but mac80211 assumes it can
		 * access fields as 2-byte aligned (e.g. for ether_addr_equal)
		 */
		int align;

		align = (unsigned long)(skb->data + sizeof(struct ethhdr)) & 3;
		if (align) {
			if (WARN_ON(skb_headroom(skb) < 3)) {
				dev_kfree_skb(skb);
				skb = NULL;
			} else {
				u8 *data = skb->data;
				size_t len = skb_headlen(skb);
				skb->data -= align;
				memmove(skb->data, data, len);
				skb_set_tail_pointer(skb, len);
			}
		}
	}
#endif

	if (skb) {
		skb->protocol = eth_type_trans(skb, dev);
		ieee80211_deliver_skb_to_local_stack(skb, rx);
	}

	if (xmit_skb) {
		/*
		 * Send to wireless media and increase priority by 256 to
		 * keep the received priority instead of reclassifying
		 * the frame (see cfg80211_classify8021d).
		 */
		xmit_skb->priority += 256;
		xmit_skb->protocol = htons(ETH_P_802_3);
		skb_reset_network_header(xmit_skb);
		skb_reset_mac_header(xmit_skb);
		dev_queue_xmit(xmit_skb);
	}
}