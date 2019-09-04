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
struct sw_flow_key {int /*<<< orphan*/  mac_proto; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  eth_dst; int /*<<< orphan*/  eth_src; } ;
struct ovs_action_push_eth {TYPE_1__ addresses; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  MAC_PROTO_ETHERNET ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_flow_key (struct sw_flow_key*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_postpush_rcsum (struct sk_buff*,struct ethhdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 

__attribute__((used)) static int push_eth(struct sk_buff *skb, struct sw_flow_key *key,
		    const struct ovs_action_push_eth *ethh)
{
	struct ethhdr *hdr;

	/* Add the new Ethernet header */
	if (skb_cow_head(skb, ETH_HLEN) < 0)
		return -ENOMEM;

	skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);

	hdr = eth_hdr(skb);
	ether_addr_copy(hdr->h_source, ethh->addresses.eth_src);
	ether_addr_copy(hdr->h_dest, ethh->addresses.eth_dst);
	hdr->h_proto = skb->protocol;

	skb_postpush_rcsum(skb, hdr, ETH_HLEN);

	/* safe right before invalidate_flow_key */
	key->mac_proto = MAC_PROTO_ETHERNET;
	invalidate_flow_key(key);
	return 0;
}