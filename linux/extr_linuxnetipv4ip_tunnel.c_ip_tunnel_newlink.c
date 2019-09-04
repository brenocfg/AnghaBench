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
struct net_device {scalar_t__ type; unsigned int hard_header_len; int /*<<< orphan*/  mtu; } ;
struct net {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_tunnel_parm {int dummy; } ;
struct ip_tunnel_net {int /*<<< orphan*/  collect_md_tun; } ;
struct ip_tunnel {unsigned int hlen; int /*<<< orphan*/  fwmark; struct ip_tunnel_parm parms; struct net* net; scalar_t__ collect_md; int /*<<< orphan*/  ip_tnl_net_id; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EEXIST ; 
 scalar_t__ ETH_MIN_MTU ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_MTU ; 
 unsigned int IP_MAX_MTU ; 
 int clamp (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct net* dev_net (struct net_device*) ; 
 int dev_set_mtu (struct net_device*,int) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ip_tunnel_add (struct ip_tunnel_net*,struct ip_tunnel*) ; 
 int ip_tunnel_bind_dev (struct net_device*) ; 
 scalar_t__ ip_tunnel_find (struct ip_tunnel_net*,struct ip_tunnel_parm*,scalar_t__) ; 
 struct ip_tunnel_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 scalar_t__ rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

int ip_tunnel_newlink(struct net_device *dev, struct nlattr *tb[],
		      struct ip_tunnel_parm *p, __u32 fwmark)
{
	struct ip_tunnel *nt;
	struct net *net = dev_net(dev);
	struct ip_tunnel_net *itn;
	int mtu;
	int err;

	nt = netdev_priv(dev);
	itn = net_generic(net, nt->ip_tnl_net_id);

	if (nt->collect_md) {
		if (rtnl_dereference(itn->collect_md_tun))
			return -EEXIST;
	} else {
		if (ip_tunnel_find(itn, p, dev->type))
			return -EEXIST;
	}

	nt->net = net;
	nt->parms = *p;
	nt->fwmark = fwmark;
	err = register_netdevice(dev);
	if (err)
		goto err_register_netdevice;

	if (dev->type == ARPHRD_ETHER && !tb[IFLA_ADDRESS])
		eth_hw_addr_random(dev);

	mtu = ip_tunnel_bind_dev(dev);
	if (tb[IFLA_MTU]) {
		unsigned int max = IP_MAX_MTU - dev->hard_header_len - nt->hlen;

		mtu = clamp(dev->mtu, (unsigned int)ETH_MIN_MTU,
			    (unsigned int)(max - sizeof(struct iphdr)));
	}

	err = dev_set_mtu(dev, mtu);
	if (err)
		goto err_dev_set_mtu;

	ip_tunnel_add(itn, nt);
	return 0;

err_dev_set_mtu:
	unregister_netdevice(dev);
err_register_netdevice:
	return err;
}