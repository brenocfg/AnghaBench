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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* devconf_all; } ;
struct net {TYPE_2__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {struct in6_addr daddr; struct in6_addr saddr; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  hop_limit; } ;
struct TYPE_3__ {int /*<<< orphan*/  hop_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  ip6_flow_hdr (struct ipv6hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static struct ipv6hdr *
synproxy_build_ip(struct net *net, struct sk_buff *skb,
		  const struct in6_addr *saddr,
		  const struct in6_addr *daddr)
{
	struct ipv6hdr *iph;

	skb_reset_network_header(skb);
	iph = skb_put(skb, sizeof(*iph));
	ip6_flow_hdr(iph, 0, 0);
	iph->hop_limit	= net->ipv6.devconf_all->hop_limit;
	iph->nexthdr	= IPPROTO_TCP;
	iph->saddr	= *saddr;
	iph->daddr	= *daddr;

	return iph;
}