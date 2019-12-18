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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_proto {TYPE_1__* ops; } ;
struct tcf_block {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int /*<<< orphan*/  rtnl; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int (* delete ) (struct tcf_proto*,void*,int*,int,struct netlink_ext_ack*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int NLM_F_ECHO ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  RTM_DELTFILTER ; 
 int /*<<< orphan*/  RTNLGRP_TC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct tcf_proto*,void*,int*,int,struct netlink_ext_ack*) ; 
 scalar_t__ tcf_fill_node (struct net*,struct sk_buff*,struct tcf_proto*,struct tcf_block*,struct Qdisc*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tfilter_del_notify(struct net *net, struct sk_buff *oskb,
			      struct nlmsghdr *n, struct tcf_proto *tp,
			      struct tcf_block *block, struct Qdisc *q,
			      u32 parent, void *fh, bool unicast, bool *last,
			      bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct sk_buff *skb;
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	int err;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb)
		return -ENOBUFS;

	if (tcf_fill_node(net, skb, tp, block, q, parent, fh, portid,
			  n->nlmsg_seq, n->nlmsg_flags, RTM_DELTFILTER,
			  rtnl_held) <= 0) {
		NL_SET_ERR_MSG(extack, "Failed to build del event notification");
		kfree_skb(skb);
		return -EINVAL;
	}

	err = tp->ops->delete(tp, fh, last, rtnl_held, extack);
	if (err) {
		kfree_skb(skb);
		return err;
	}

	if (unicast)
		err = netlink_unicast(net->rtnl, skb, portid, MSG_DONTWAIT);
	else
		err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
				     n->nlmsg_flags & NLM_F_ECHO);
	if (err < 0)
		NL_SET_ERR_MSG(extack, "Failed to send filter delete notification");

	if (err > 0)
		err = 0;
	return err;
}