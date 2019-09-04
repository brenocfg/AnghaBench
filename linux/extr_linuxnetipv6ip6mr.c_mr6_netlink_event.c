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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct mr_table {int /*<<< orphan*/  maxvif; int /*<<< orphan*/  net; } ;
struct TYPE_2__ {scalar_t__ mfc_parent; } ;
struct mfc6_cache {TYPE_1__ _c; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAXMIFS ; 
 int /*<<< orphan*/  RTNLGRP_IPV6_MROUTE ; 
 int ip6mr_fill_mroute (struct mr_table*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mfc6_cache*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mr6_msgsize (int,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mr6_netlink_event(struct mr_table *mrt, struct mfc6_cache *mfc,
			      int cmd)
{
	struct net *net = read_pnet(&mrt->net);
	struct sk_buff *skb;
	int err = -ENOBUFS;

	skb = nlmsg_new(mr6_msgsize(mfc->_c.mfc_parent >= MAXMIFS, mrt->maxvif),
			GFP_ATOMIC);
	if (!skb)
		goto errout;

	err = ip6mr_fill_mroute(mrt, skb, 0, 0, mfc, cmd, 0);
	if (err < 0)
		goto errout;

	rtnl_notify(skb, net, 0, RTNLGRP_IPV6_MROUTE, NULL, GFP_ATOMIC);
	return;

errout:
	kfree_skb(skb);
	if (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_MROUTE, err);
}