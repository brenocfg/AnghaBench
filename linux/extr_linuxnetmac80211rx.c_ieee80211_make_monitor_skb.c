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
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_rate {int dummy; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_add_rx_radiotap_header (struct ieee80211_local*,struct sk_buff*,struct ieee80211_rate*,int,int) ; 
 int ieee80211_rx_radiotap_hdrlen (struct ieee80211_local*,struct ieee80211_rx_status*,struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
ieee80211_make_monitor_skb(struct ieee80211_local *local,
			   struct sk_buff **origskb,
			   struct ieee80211_rate *rate,
			   int rtap_space, bool use_origskb)
{
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(*origskb);
	int rt_hdrlen, needed_headroom;
	struct sk_buff *skb;

	/* room for the radiotap header based on driver features */
	rt_hdrlen = ieee80211_rx_radiotap_hdrlen(local, status, *origskb);
	needed_headroom = rt_hdrlen - rtap_space;

	if (use_origskb) {
		/* only need to expand headroom if necessary */
		skb = *origskb;
		*origskb = NULL;

		/*
		 * This shouldn't trigger often because most devices have an
		 * RX header they pull before we get here, and that should
		 * be big enough for our radiotap information. We should
		 * probably export the length to drivers so that we can have
		 * them allocate enough headroom to start with.
		 */
		if (skb_headroom(skb) < needed_headroom &&
		    pskb_expand_head(skb, needed_headroom, 0, GFP_ATOMIC)) {
			dev_kfree_skb(skb);
			return NULL;
		}
	} else {
		/*
		 * Need to make a copy and possibly remove radiotap header
		 * and FCS from the original.
		 */
		skb = skb_copy_expand(*origskb, needed_headroom, 0, GFP_ATOMIC);

		if (!skb)
			return NULL;
	}

	/* prepend radiotap information */
	ieee80211_add_rx_radiotap_header(local, skb, rate, rt_hdrlen, true);

	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);

	return skb;
}