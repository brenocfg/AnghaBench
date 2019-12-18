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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct net_bridge_port {int /*<<< orphan*/  port_no; struct net_bridge* br; struct net_device* dev; } ;
struct net_bridge {struct net_device* dev; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RTEXT_FILTER_BRVLAN_COMPRESSED ; 
 int /*<<< orphan*/  RTNLGRP_LINK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  br_debug (struct net_bridge const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int br_fill_ifinfo (struct sk_buff*,struct net_bridge_port const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  br_nlmsg_size (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

void br_ifinfo_notify(int event, const struct net_bridge *br,
		      const struct net_bridge_port *port)
{
	u32 filter = RTEXT_FILTER_BRVLAN_COMPRESSED;
	struct net_device *dev;
	struct sk_buff *skb;
	int err = -ENOBUFS;
	struct net *net;
	u16 port_no = 0;

	if (WARN_ON(!port && !br))
		return;

	if (port) {
		dev = port->dev;
		br = port->br;
		port_no = port->port_no;
	} else {
		dev = br->dev;
	}

	net = dev_net(dev);
	br_debug(br, "port %u(%s) event %d\n", port_no, dev->name, event);

	skb = nlmsg_new(br_nlmsg_size(dev, filter), GFP_ATOMIC);
	if (skb == NULL)
		goto errout;

	err = br_fill_ifinfo(skb, port, 0, 0, event, 0, filter, dev);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in br_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	rtnl_notify(skb, net, 0, RTNLGRP_LINK, NULL, GFP_ATOMIC);
	return;
errout:
	rtnl_set_sk_err(net, RTNLGRP_LINK, err);
}