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
struct xfrm_if_parms {int /*<<< orphan*/  name; } ;
struct xfrm_if {struct xfrm_if_parms p; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IFLA_IFNAME ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int PTR_ERR_OR_ZERO (struct xfrm_if*) ; 
 struct net* dev_net (struct net_device*) ; 
 struct xfrm_if* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_strlcpy (int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 struct xfrm_if* xfrmi_locate (struct net*,struct xfrm_if_parms*,int) ; 
 int /*<<< orphan*/  xfrmi_netlink_parms (struct nlattr**,struct xfrm_if_parms*) ; 

__attribute__((used)) static int xfrmi_newlink(struct net *src_net, struct net_device *dev,
			struct nlattr *tb[], struct nlattr *data[],
			struct netlink_ext_ack *extack)
{
	struct net *net = dev_net(dev);
	struct xfrm_if_parms *p;
	struct xfrm_if *xi;

	xi = netdev_priv(dev);
	p = &xi->p;

	xfrmi_netlink_parms(data, p);

	if (!tb[IFLA_IFNAME])
		return -EINVAL;

	nla_strlcpy(p->name, tb[IFLA_IFNAME], IFNAMSIZ);

	xi = xfrmi_locate(net, p, 1);
	return PTR_ERR_OR_ZERO(xi);
}