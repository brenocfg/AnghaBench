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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct ipv6hdr {scalar_t__ nexthdr; int hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct flow_ports {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct flow_offload_tuple {scalar_t__ l4proto; int /*<<< orphan*/  iifidx; int /*<<< orphan*/  l3proto; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_v6; int /*<<< orphan*/  src_v6; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static int nf_flow_tuple_ipv6(struct sk_buff *skb, const struct net_device *dev,
			      struct flow_offload_tuple *tuple)
{
	struct flow_ports *ports;
	struct ipv6hdr *ip6h;
	unsigned int thoff;

	if (!pskb_may_pull(skb, sizeof(*ip6h)))
		return -1;

	ip6h = ipv6_hdr(skb);

	if (ip6h->nexthdr != IPPROTO_TCP &&
	    ip6h->nexthdr != IPPROTO_UDP)
		return -1;

	if (ip6h->hop_limit <= 1)
		return -1;

	thoff = sizeof(*ip6h);
	if (!pskb_may_pull(skb, thoff + sizeof(*ports)))
		return -1;

	ports = (struct flow_ports *)(skb_network_header(skb) + thoff);

	tuple->src_v6		= ip6h->saddr;
	tuple->dst_v6		= ip6h->daddr;
	tuple->src_port		= ports->source;
	tuple->dst_port		= ports->dest;
	tuple->l3proto		= AF_INET6;
	tuple->l4proto		= ip6h->nexthdr;
	tuple->iifidx		= dev->ifindex;

	return 0;
}