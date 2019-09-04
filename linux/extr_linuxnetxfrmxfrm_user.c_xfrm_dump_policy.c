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
struct xfrm_policy_walk {int dummy; } ;
struct xfrm_dump_info {int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; struct sk_buff* out_skb; int /*<<< orphan*/  in_skb; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {TYPE_1__* nlh; int /*<<< orphan*/  skb; scalar_t__ args; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  dump_one_policy ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_policy_walk (struct net*,struct xfrm_policy_walk*,int /*<<< orphan*/ ,struct xfrm_dump_info*) ; 

__attribute__((used)) static int xfrm_dump_policy(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_policy_walk *walk = (struct xfrm_policy_walk *)cb->args;
	struct xfrm_dump_info info;

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nlmsg_seq = cb->nlh->nlmsg_seq;
	info.nlmsg_flags = NLM_F_MULTI;

	(void) xfrm_policy_walk(net, walk, dump_one_policy, &info);

	return skb->len;
}