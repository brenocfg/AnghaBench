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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  RTNLGRP_LINK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net* dev_net (struct net_device*) ; 
 size_t if_nlmsg_size (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (size_t,int /*<<< orphan*/ ) ; 
 int rtnl_fill_ifinfo (struct sk_buff*,struct net_device*,struct net*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

struct sk_buff *rtmsg_ifinfo_build_skb(int type, struct net_device *dev,
				       unsigned int change,
				       u32 event, gfp_t flags, int *new_nsid,
				       int new_ifindex)
{
	struct net *net = dev_net(dev);
	struct sk_buff *skb;
	int err = -ENOBUFS;
	size_t if_info_size;

	skb = nlmsg_new((if_info_size = if_nlmsg_size(dev, 0)), flags);
	if (skb == NULL)
		goto errout;

	err = rtnl_fill_ifinfo(skb, dev, dev_net(dev),
			       type, 0, 0, change, 0, 0, event,
			       new_nsid, new_ifindex, -1, flags);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in if_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	return skb;
errout:
	if (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_LINK, err);
	return NULL;
}