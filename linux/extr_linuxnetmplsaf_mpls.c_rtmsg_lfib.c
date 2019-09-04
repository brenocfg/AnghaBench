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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct net {int dummy; } ;
struct mpls_route {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTNLGRP_MPLS_ROUTE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lfib_nlmsg_size (struct mpls_route*) ; 
 int mpls_dump_route (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mpls_route*,unsigned int) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtmsg_lfib(int event, u32 label, struct mpls_route *rt,
		       struct nlmsghdr *nlh, struct net *net, u32 portid,
		       unsigned int nlm_flags)
{
	struct sk_buff *skb;
	u32 seq = nlh ? nlh->nlmsg_seq : 0;
	int err = -ENOBUFS;

	skb = nlmsg_new(lfib_nlmsg_size(rt), GFP_KERNEL);
	if (skb == NULL)
		goto errout;

	err = mpls_dump_route(skb, portid, seq, event, label, rt, nlm_flags);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in lfib_nlmsg_size */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	rtnl_notify(skb, net, portid, RTNLGRP_MPLS_ROUTE, nlh, GFP_KERNEL);

	return;
errout:
	if (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_MPLS_ROUTE, err);
}