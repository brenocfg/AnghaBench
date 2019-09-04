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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_idev; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 int ip6_local_out (struct net*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int net_xmit_errno (int) ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

int ip6_send_skb(struct sk_buff *skb)
{
	struct net *net = sock_net(skb->sk);
	struct rt6_info *rt = (struct rt6_info *)skb_dst(skb);
	int err;

	err = ip6_local_out(net, skb->sk, skb);
	if (err) {
		if (err > 0)
			err = net_xmit_errno(err);
		if (err)
			IP6_INC_STATS(net, rt->rt6i_idev,
				      IPSTATS_MIB_OUTDISCARDS);
	}

	return err;
}