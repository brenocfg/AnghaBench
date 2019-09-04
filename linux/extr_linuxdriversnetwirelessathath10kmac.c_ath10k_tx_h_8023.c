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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct rfc1042_hdr {int /*<<< orphan*/  snap_type; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/ * h_source; int /*<<< orphan*/ * h_dest; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ieee80211_get_DA (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/ * ieee80211_get_SA (struct ieee80211_hdr*) ; 
 size_t ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void ath10k_tx_h_8023(struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr;
	struct rfc1042_hdr *rfc1042;
	struct ethhdr *eth;
	size_t hdrlen;
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
	__be16 type;

	hdr = (void *)skb->data;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	rfc1042 = (void *)skb->data + hdrlen;

	ether_addr_copy(da, ieee80211_get_DA(hdr));
	ether_addr_copy(sa, ieee80211_get_SA(hdr));
	type = rfc1042->snap_type;

	skb_pull(skb, hdrlen + sizeof(*rfc1042));
	skb_push(skb, sizeof(*eth));

	eth = (void *)skb->data;
	ether_addr_copy(eth->h_dest, da);
	ether_addr_copy(eth->h_source, sa);
	eth->h_proto = type;
}