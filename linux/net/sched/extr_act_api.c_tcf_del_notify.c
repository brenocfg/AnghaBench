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
typedef  int /*<<< orphan*/  u32 ;
struct tc_action {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NLMSG_GOODSIZE ; 
 int NLM_F_ECHO ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  RTM_DELACTION ; 
 int /*<<< orphan*/  RTNLGRP_TC ; 
 struct sk_buff* alloc_skb (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int rtnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tca_get_fill (struct sk_buff*,struct tc_action**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tcf_action_delete (struct net*,struct tc_action**) ; 

__attribute__((used)) static int
tcf_del_notify(struct net *net, struct nlmsghdr *n, struct tc_action *actions[],
	       u32 portid, size_t attr_size, struct netlink_ext_ack *extack)
{
	int ret;
	struct sk_buff *skb;

	skb = alloc_skb(attr_size <= NLMSG_GOODSIZE ? NLMSG_GOODSIZE : attr_size,
			GFP_KERNEL);
	if (!skb)
		return -ENOBUFS;

	if (tca_get_fill(skb, actions, portid, n->nlmsg_seq, 0, RTM_DELACTION,
			 0, 2) <= 0) {
		NL_SET_ERR_MSG(extack, "Failed to fill netlink TC action attributes");
		kfree_skb(skb);
		return -EINVAL;
	}

	/* now do the delete */
	ret = tcf_action_delete(net, actions);
	if (ret < 0) {
		NL_SET_ERR_MSG(extack, "Failed to delete TC action");
		kfree_skb(skb);
		return ret;
	}

	ret = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
			     n->nlmsg_flags & NLM_F_ECHO);
	if (ret > 0)
		return 0;
	return ret;
}