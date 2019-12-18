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
typedef  int u8 ;
struct sk_buff {TYPE_1__* dev; scalar_t__ data; } ;
struct net {int dummy; } ;
struct inet6_skb_parm {int dummy; } ;
struct icmp6hdr {scalar_t__ icmp6_type; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 scalar_t__ ICMPV6_ECHO_REQUEST ; 
 int ICMPV6_INFOMSG_MASK ; 
 int ICMPV6_PKT_TOOBIG ; 
 int NDISC_REDIRECT ; 
 struct net* dev_net (TYPE_1__*) ; 
 int /*<<< orphan*/  ip6_redirect (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_update_pmtu (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ping_err (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net_uid (struct net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int icmpv6_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
		       u8 type, u8 code, int offset, __be32 info)
{
	/* icmpv6_notify checks 8 bytes can be pulled, icmp6hdr is 8 bytes */
	struct icmp6hdr *icmp6 = (struct icmp6hdr *) (skb->data + offset);
	struct net *net = dev_net(skb->dev);

	if (type == ICMPV6_PKT_TOOBIG)
		ip6_update_pmtu(skb, net, info, skb->dev->ifindex, 0, sock_net_uid(net, NULL));
	else if (type == NDISC_REDIRECT)
		ip6_redirect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NULL));

	if (!(type & ICMPV6_INFOMSG_MASK))
		if (icmp6->icmp6_type == ICMPV6_ECHO_REQUEST)
			ping_err(skb, offset, ntohl(info));

	return 0;
}