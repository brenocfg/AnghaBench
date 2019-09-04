#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct sw_flow_key {TYPE_1__ eth; } ;
struct sk_buff {int dummy; } ;
struct ovs_key_ethernet {int /*<<< orphan*/  eth_dst; int /*<<< orphan*/  eth_src; } ;
struct TYPE_6__ {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy_masked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_ensure_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  skb_postpush_rcsum (struct sk_buff*,TYPE_2__*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int set_eth_addr(struct sk_buff *skb, struct sw_flow_key *flow_key,
			const struct ovs_key_ethernet *key,
			const struct ovs_key_ethernet *mask)
{
	int err;

	err = skb_ensure_writable(skb, ETH_HLEN);
	if (unlikely(err))
		return err;

	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_ALEN * 2);

	ether_addr_copy_masked(eth_hdr(skb)->h_source, key->eth_src,
			       mask->eth_src);
	ether_addr_copy_masked(eth_hdr(skb)->h_dest, key->eth_dst,
			       mask->eth_dst);

	skb_postpush_rcsum(skb, eth_hdr(skb), ETH_ALEN * 2);

	ether_addr_copy(flow_key->eth.src, eth_hdr(skb)->h_source);
	ether_addr_copy(flow_key->eth.dst, eth_hdr(skb)->h_dest);
	return 0;
}