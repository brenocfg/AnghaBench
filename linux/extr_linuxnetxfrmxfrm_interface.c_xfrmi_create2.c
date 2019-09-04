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
struct xfrmi_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct xfrm_if {TYPE_1__ p; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/ * rtnl_link_ops; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 struct xfrmi_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct xfrm_if* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrmi_link (struct xfrmi_net*,struct xfrm_if*) ; 
 int /*<<< orphan*/  xfrmi_link_ops ; 
 int /*<<< orphan*/  xfrmi_net_id ; 

__attribute__((used)) static int xfrmi_create2(struct net_device *dev)
{
	struct xfrm_if *xi = netdev_priv(dev);
	struct net *net = dev_net(dev);
	struct xfrmi_net *xfrmn = net_generic(net, xfrmi_net_id);
	int err;

	dev->rtnl_link_ops = &xfrmi_link_ops;
	err = register_netdevice(dev);
	if (err < 0)
		goto out;

	strcpy(xi->p.name, dev->name);

	dev_hold(dev);
	xfrmi_link(xfrmn, xi);

	return 0;

out:
	return err;
}