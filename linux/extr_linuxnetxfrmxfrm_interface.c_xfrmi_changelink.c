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
struct xfrm_if {int /*<<< orphan*/  p; struct net_device* dev; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ IS_ERR_OR_NULL (struct xfrm_if*) ; 
 struct net* dev_net (struct net_device*) ; 
 struct xfrm_if* netdev_priv (struct net_device*) ; 
 struct xfrm_if* xfrmi_locate (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrmi_netlink_parms (struct nlattr**,int /*<<< orphan*/ *) ; 
 int xfrmi_update (struct xfrm_if*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xfrmi_changelink(struct net_device *dev, struct nlattr *tb[],
			   struct nlattr *data[],
			   struct netlink_ext_ack *extack)
{
	struct xfrm_if *xi = netdev_priv(dev);
	struct net *net = dev_net(dev);

	xfrmi_netlink_parms(data, &xi->p);

	xi = xfrmi_locate(net, &xi->p, 0);

	if (IS_ERR_OR_NULL(xi)) {
		xi = netdev_priv(dev);
	} else {
		if (xi->dev != dev)
			return -EEXIST;
	}

	return xfrmi_update(xi, &xi->p);
}