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
struct nl_info {int /*<<< orphan*/  nl_net; TYPE_1__* nlh; int /*<<< orphan*/  portid; } ;
struct nexthop {int dummy; } ;
struct TYPE_2__ {unsigned int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  RTNLGRP_NEXTHOP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nh_fill_node (struct sk_buff*,struct nexthop*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nh_nlmsg_size (struct nexthop*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nexthop_notify(int event, struct nexthop *nh, struct nl_info *info)
{
	unsigned int nlflags = info->nlh ? info->nlh->nlmsg_flags : 0;
	u32 seq = info->nlh ? info->nlh->nlmsg_seq : 0;
	struct sk_buff *skb;
	int err = -ENOBUFS;

	skb = nlmsg_new(nh_nlmsg_size(nh), gfp_any());
	if (!skb)
		goto errout;

	err = nh_fill_node(skb, nh, event, info->portid, seq, nlflags);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in nh_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}

	rtnl_notify(skb, info->nl_net, info->portid, RTNLGRP_NEXTHOP,
		    info->nlh, gfp_any());
	return;
errout:
	if (err < 0)
		rtnl_set_sk_err(info->nl_net, RTNLGRP_NEXTHOP, err);
}