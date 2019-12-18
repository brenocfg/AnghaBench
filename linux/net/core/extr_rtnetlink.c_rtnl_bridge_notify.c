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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int (* ndo_bridge_getlink ) (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RTNLGRP_LINK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bridge_nlmsg_size () ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtnl_bridge_notify(struct net_device *dev)
{
	struct net *net = dev_net(dev);
	struct sk_buff *skb;
	int err = -EOPNOTSUPP;

	if (!dev->netdev_ops->ndo_bridge_getlink)
		return 0;

	skb = nlmsg_new(bridge_nlmsg_size(), GFP_ATOMIC);
	if (!skb) {
		err = -ENOMEM;
		goto errout;
	}

	err = dev->netdev_ops->ndo_bridge_getlink(skb, 0, 0, dev, 0, 0);
	if (err < 0)
		goto errout;

	if (!skb->len)
		goto errout;

	rtnl_notify(skb, net, 0, RTNLGRP_LINK, NULL, GFP_ATOMIC);
	return 0;
errout:
	WARN_ON(err == -EMSGSIZE);
	kfree_skb(skb);
	if (err)
		rtnl_set_sk_err(net, RTNLGRP_LINK, err);
	return err;
}