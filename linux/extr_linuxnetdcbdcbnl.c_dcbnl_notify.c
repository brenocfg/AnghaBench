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
struct nlmsghdr {int dummy; } ;
struct net_device {struct dcbnl_rtnl_ops* dcbnl_ops; } ;
struct net {int dummy; } ;
struct dcbnl_rtnl_ops {int dummy; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_VER_IEEE ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTNLGRP_DCB ; 
 int dcbnl_cee_fill (struct sk_buff*,struct net_device*) ; 
 int dcbnl_ieee_fill (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* dcbnl_newmsg (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr**) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dcbnl_notify(struct net_device *dev, int event, int cmd,
			u32 seq, u32 portid, int dcbx_ver)
{
	struct net *net = dev_net(dev);
	struct sk_buff *skb;
	struct nlmsghdr *nlh;
	const struct dcbnl_rtnl_ops *ops = dev->dcbnl_ops;
	int err;

	if (!ops)
		return -EOPNOTSUPP;

	skb = dcbnl_newmsg(event, cmd, portid, seq, 0, &nlh);
	if (!skb)
		return -ENOBUFS;

	if (dcbx_ver == DCB_CAP_DCBX_VER_IEEE)
		err = dcbnl_ieee_fill(skb, dev);
	else
		err = dcbnl_cee_fill(skb, dev);

	if (err < 0) {
		/* Report error to broadcast listeners */
		nlmsg_free(skb);
		rtnl_set_sk_err(net, RTNLGRP_DCB, err);
	} else {
		/* End nlmsg and notify broadcast listeners */
		nlmsg_end(skb, nlh);
		rtnl_notify(skb, net, 0, RTNLGRP_DCB, NULL, GFP_KERNEL);
	}

	return err;
}