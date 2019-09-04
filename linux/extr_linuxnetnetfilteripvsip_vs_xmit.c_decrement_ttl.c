#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct netns_ipvs {struct net* net; } ;
struct net {int dummy; } ;
struct iphdr {int dummy; } ;
struct TYPE_3__ {int ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_EXC_TTL ; 
 int /*<<< orphan*/  ICMP_TIME_EXCEEDED ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  __IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_decrease_ttl (TYPE_1__*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int) ; 

__attribute__((used)) static inline bool decrement_ttl(struct netns_ipvs *ipvs,
				 int skb_af,
				 struct sk_buff *skb)
{
	struct net *net = ipvs->net;

#ifdef CONFIG_IP_VS_IPV6
	if (skb_af == AF_INET6) {
		struct dst_entry *dst = skb_dst(skb);

		/* check and decrement ttl */
		if (ipv6_hdr(skb)->hop_limit <= 1) {
			struct inet6_dev *idev = __in6_dev_get_safely(skb->dev);

			/* Force OUTPUT device used as source address */
			skb->dev = dst->dev;
			icmpv6_send(skb, ICMPV6_TIME_EXCEED,
				    ICMPV6_EXC_HOPLIMIT, 0);
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);

			return false;
		}

		/* don't propagate ttl change to cloned packets */
		if (!skb_make_writable(skb, sizeof(struct ipv6hdr)))
			return false;

		ipv6_hdr(skb)->hop_limit--;
	} else
#endif
	{
		if (ip_hdr(skb)->ttl <= 1) {
			/* Tell the sender its packet died... */
			__IP_INC_STATS(net, IPSTATS_MIB_INHDRERRORS);
			icmp_send(skb, ICMP_TIME_EXCEEDED, ICMP_EXC_TTL, 0);
			return false;
		}

		/* don't propagate ttl change to cloned packets */
		if (!skb_make_writable(skb, sizeof(struct iphdr)))
			return false;

		/* Decrease ttl */
		ip_decrease_ttl(ip_hdr(skb));
	}

	return true;
}