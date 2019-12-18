#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  disable_ipv6; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 TYPE_4__* IP6CB (struct sk_buff*) ; 
 int IP6SKB_REROUTED ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int NF_HOOK_COND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct sock*,struct sk_buff*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NF_INET_POST_ROUTING ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct inet6_dev* ip6_dst_idev (TYPE_2__*) ; 
 int /*<<< orphan*/  ip6_finish_output ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ip6_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct net_device *dev = skb_dst(skb)->dev;
	struct inet6_dev *idev = ip6_dst_idev(skb_dst(skb));

	skb->protocol = htons(ETH_P_IPV6);
	skb->dev = dev;

	if (unlikely(idev->cnf.disable_ipv6)) {
		IP6_INC_STATS(net, idev, IPSTATS_MIB_OUTDISCARDS);
		kfree_skb(skb);
		return 0;
	}

	return NF_HOOK_COND(NFPROTO_IPV6, NF_INET_POST_ROUTING,
			    net, sk, skb, NULL, dev,
			    ip6_finish_output,
			    !(IP6CB(skb)->flags & IP6SKB_REROUTED));
}