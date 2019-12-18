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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct net {int dummy; } ;
struct Qdisc_class_ops {int (* delete ) (struct Qdisc*,unsigned long) ;} ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int NLM_F_ECHO ; 
 int /*<<< orphan*/  RTM_DELTCLASS ; 
 int /*<<< orphan*/  RTNLGRP_TC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int rtnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct Qdisc*,unsigned long) ; 
 scalar_t__ tc_fill_tclass (struct sk_buff*,struct Qdisc*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tclass_del_notify(struct net *net,
			     const struct Qdisc_class_ops *cops,
			     struct sk_buff *oskb, struct nlmsghdr *n,
			     struct Qdisc *q, unsigned long cl)
{
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	struct sk_buff *skb;
	int err = 0;

	if (!cops->delete)
		return -EOPNOTSUPP;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb)
		return -ENOBUFS;

	if (tc_fill_tclass(skb, q, cl, portid, n->nlmsg_seq, 0,
			   RTM_DELTCLASS) < 0) {
		kfree_skb(skb);
		return -EINVAL;
	}

	err = cops->delete(q, cl);
	if (err) {
		kfree_skb(skb);
		return err;
	}

	err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
			     n->nlmsg_flags & NLM_F_ECHO);
	if (err > 0)
		err = 0;
	return err;
}