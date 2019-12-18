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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {scalar_t__ type; } ;
struct net {int dummy; } ;
struct ip_tunnel_encap {int dummy; } ;
struct ip6_tnl {int /*<<< orphan*/  net; struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_MTU ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ip6_tnl_change_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int ip6_tnl_encap_setup (struct ip6_tnl*,struct ip_tunnel_encap*) ; 
 scalar_t__ ip6gre_netlink_encap_parms (struct nlattr**,struct ip_tunnel_encap*) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int register_netdevice (struct net_device*) ; 

__attribute__((used)) static int ip6gre_newlink_common(struct net *src_net, struct net_device *dev,
				 struct nlattr *tb[], struct nlattr *data[],
				 struct netlink_ext_ack *extack)
{
	struct ip6_tnl *nt;
	struct ip_tunnel_encap ipencap;
	int err;

	nt = netdev_priv(dev);

	if (ip6gre_netlink_encap_parms(data, &ipencap)) {
		int err = ip6_tnl_encap_setup(nt, &ipencap);

		if (err < 0)
			return err;
	}

	if (dev->type == ARPHRD_ETHER && !tb[IFLA_ADDRESS])
		eth_hw_addr_random(dev);

	nt->dev = dev;
	nt->net = dev_net(dev);

	err = register_netdevice(dev);
	if (err)
		goto out;

	if (tb[IFLA_MTU])
		ip6_tnl_change_mtu(dev, nla_get_u32(tb[IFLA_MTU]));

	dev_hold(dev);

out:
	return err;
}