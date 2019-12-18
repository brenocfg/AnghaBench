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
struct xfrm_if_parms {int dummy; } ;
struct xfrm_if {struct net_device* dev; struct net* net; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 struct xfrm_if* netdev_priv (struct net_device*) ; 
 struct xfrm_if* xfrmi_locate (struct net*,struct xfrm_if_parms*) ; 
 int /*<<< orphan*/  xfrmi_netlink_parms (struct nlattr**,struct xfrm_if_parms*) ; 
 int xfrmi_update (struct xfrm_if*,struct xfrm_if_parms*) ; 

__attribute__((used)) static int xfrmi_changelink(struct net_device *dev, struct nlattr *tb[],
			   struct nlattr *data[],
			   struct netlink_ext_ack *extack)
{
	struct xfrm_if *xi = netdev_priv(dev);
	struct net *net = xi->net;
	struct xfrm_if_parms p;

	xfrmi_netlink_parms(data, &p);
	xi = xfrmi_locate(net, &p);
	if (!xi) {
		xi = netdev_priv(dev);
	} else {
		if (xi->dev != dev)
			return -EEXIST;
	}

	return xfrmi_update(xi, &p);
}