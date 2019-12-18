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
struct net_device {int dummy; } ;
struct net_bridge_port {TYPE_1__* dev; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NTF_SELF ; 
 int /*<<< orphan*/  RTNLGRP_MDB ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_populate_rtr_fill (struct sk_buff*,struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_rtr_nlmsg_size () ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

void br_rtr_notify(struct net_device *dev, struct net_bridge_port *port,
		   int type)
{
	struct net *net = dev_net(dev);
	struct sk_buff *skb;
	int err = -ENOBUFS;
	int ifindex;

	ifindex = port ? port->dev->ifindex : 0;
	skb = nlmsg_new(rtnl_rtr_nlmsg_size(), GFP_ATOMIC);
	if (!skb)
		goto errout;

	err = nlmsg_populate_rtr_fill(skb, dev, ifindex, 0, 0, type, NTF_SELF);
	if (err < 0) {
		kfree_skb(skb);
		goto errout;
	}

	rtnl_notify(skb, net, 0, RTNLGRP_MDB, NULL, GFP_ATOMIC);
	return;

errout:
	rtnl_set_sk_err(net, RTNLGRP_MDB, err);
}