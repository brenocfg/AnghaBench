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
struct sk_buff {scalar_t__ len; } ;
struct nlmsghdr {int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct net {int dummy; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int NLM_F_ECHO ; 
 int /*<<< orphan*/  NLM_F_REPLACE ; 
 int /*<<< orphan*/  RTM_DELQDISC ; 
 int /*<<< orphan*/  RTM_NEWQDISC ; 
 int /*<<< orphan*/  RTNLGRP_TC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int rtnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tc_fill_qdisc (struct sk_buff*,struct Qdisc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_qdisc_dump_ignore (struct Qdisc*,int) ; 

__attribute__((used)) static int qdisc_notify(struct net *net, struct sk_buff *oskb,
			struct nlmsghdr *n, u32 clid,
			struct Qdisc *old, struct Qdisc *new)
{
	struct sk_buff *skb;
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb)
		return -ENOBUFS;

	if (old && !tc_qdisc_dump_ignore(old, false)) {
		if (tc_fill_qdisc(skb, old, clid, portid, n->nlmsg_seq,
				  0, RTM_DELQDISC) < 0)
			goto err_out;
	}
	if (new && !tc_qdisc_dump_ignore(new, false)) {
		if (tc_fill_qdisc(skb, new, clid, portid, n->nlmsg_seq,
				  old ? NLM_F_REPLACE : 0, RTM_NEWQDISC) < 0)
			goto err_out;
	}

	if (skb->len)
		return rtnetlink_send(skb, net, portid, RTNLGRP_TC,
				      n->nlmsg_flags & NLM_F_ECHO);

err_out:
	kfree_skb(skb);
	return -EINVAL;
}