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
struct sk_buff {int dummy; } ;
struct dn_ifaddr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTNLGRP_DECnet_IFADDR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_ifaddr_nlmsg_size () ; 
 int dn_nl_fill_ifaddr (struct sk_buff*,struct dn_ifaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dn_ifaddr_notify(int event, struct dn_ifaddr *ifa)
{
	struct sk_buff *skb;
	int err = -ENOBUFS;

	skb = alloc_skb(dn_ifaddr_nlmsg_size(), GFP_KERNEL);
	if (skb == NULL)
		goto errout;

	err = dn_nl_fill_ifaddr(skb, ifa, 0, 0, event, 0);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in dn_ifaddr_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	rtnl_notify(skb, &init_net, 0, RTNLGRP_DECnet_IFADDR, NULL, GFP_KERNEL);
	return;
errout:
	if (err < 0)
		rtnl_set_sk_err(&init_net, RTNLGRP_DECnet_IFADDR, err);
}