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
struct net {int dummy; } ;
struct ipv6_devconf {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTNLGRP_IPV6_NETCONF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int inet6_netconf_fill_devconf (struct sk_buff*,int,struct ipv6_devconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inet6_netconf_msgsize_devconf (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

void inet6_netconf_notify_devconf(struct net *net, int event, int type,
				  int ifindex, struct ipv6_devconf *devconf)
{
	struct sk_buff *skb;
	int err = -ENOBUFS;

	skb = nlmsg_new(inet6_netconf_msgsize_devconf(type), GFP_KERNEL);
	if (!skb)
		goto errout;

	err = inet6_netconf_fill_devconf(skb, ifindex, devconf, 0, 0,
					 event, 0, type);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in inet6_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	rtnl_notify(skb, net, 0, RTNLGRP_IPV6_NETCONF, NULL, GFP_KERNEL);
	return;
errout:
	rtnl_set_sk_err(net, RTNLGRP_IPV6_NETCONF, err);
}