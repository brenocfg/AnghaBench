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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  scalar_t__ u8 ;
struct xfrm_state {int dummy; } ;
struct sk_buff {TYPE_1__* dev; int /*<<< orphan*/  mark; scalar_t__ data; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct ip_auth_hdr {int /*<<< orphan*/  spi; } ;
struct inet6_skb_parm {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ ICMPV6_PKT_TOOBIG ; 
 int /*<<< orphan*/  IPPROTO_AH ; 
 scalar_t__ NDISC_REDIRECT ; 
 struct net* dev_net (TYPE_1__*) ; 
 int /*<<< orphan*/  ip6_redirect (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_update_pmtu (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net_uid (struct net*,int /*<<< orphan*/ *) ; 
 struct xfrm_state* xfrm_state_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 

__attribute__((used)) static int ah6_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
		   u8 type, u8 code, int offset, __be32 info)
{
	struct net *net = dev_net(skb->dev);
	struct ipv6hdr *iph = (struct ipv6hdr *)skb->data;
	struct ip_auth_hdr *ah = (struct ip_auth_hdr *)(skb->data+offset);
	struct xfrm_state *x;

	if (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_REDIRECT)
		return 0;

	x = xfrm_state_lookup(net, skb->mark, (xfrm_address_t *)&iph->daddr, ah->spi, IPPROTO_AH, AF_INET6);
	if (!x)
		return 0;

	if (type == NDISC_REDIRECT)
		ip6_redirect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NULL));
	else
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, NULL));
	xfrm_state_put(x);

	return 0;
}