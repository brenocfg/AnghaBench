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
struct sk_buff {scalar_t__ data; } ;
struct net_offload {int flags; } ;
struct ipv6_opt_hdr {int nexthdr; } ;

/* Variables and functions */
 int INET6_PROTO_GSO_EXTHDR ; 
 int NEXTHDR_HOP ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * inet6_offloads ; 
 int ipv6_optlen (struct ipv6_opt_hdr*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 struct net_offload* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipv6_gso_pull_exthdrs(struct sk_buff *skb, int proto)
{
	const struct net_offload *ops = NULL;

	for (;;) {
		struct ipv6_opt_hdr *opth;
		int len;

		if (proto != NEXTHDR_HOP) {
			ops = rcu_dereference(inet6_offloads[proto]);

			if (unlikely(!ops))
				break;

			if (!(ops->flags & INET6_PROTO_GSO_EXTHDR))
				break;
		}

		if (unlikely(!pskb_may_pull(skb, 8)))
			break;

		opth = (void *)skb->data;
		len = ipv6_optlen(opth);

		if (unlikely(!pskb_may_pull(skb, len)))
			break;

		opth = (void *)skb->data;
		proto = opth->nexthdr;
		__skb_pull(skb, len);
	}

	return proto;
}