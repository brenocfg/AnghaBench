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
struct net_device {scalar_t__ hard_header_len; scalar_t__ max_mtu; int /*<<< orphan*/  min_mtu; } ;
struct net {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_tunnel_parm {int dummy; } ;
struct ip_tunnel_net {int /*<<< orphan*/  rtnl_link_ops; } ;
struct ip_tunnel {int hlen; } ;

/* Variables and functions */
 struct ip_tunnel* ERR_CAST (struct net_device*) ; 
 struct ip_tunnel* ERR_PTR (int) ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 scalar_t__ IP_MAX_MTU ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 struct net_device* __ip_tunnel_create (struct net*,int /*<<< orphan*/ ,struct ip_tunnel_parm*) ; 
 int dev_set_mtu (struct net_device*,int) ; 
 int /*<<< orphan*/  ip_tunnel_add (struct ip_tunnel_net*,struct ip_tunnel*) ; 
 int ip_tunnel_bind_dev (struct net_device*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static struct ip_tunnel *ip_tunnel_create(struct net *net,
					  struct ip_tunnel_net *itn,
					  struct ip_tunnel_parm *parms)
{
	struct ip_tunnel *nt;
	struct net_device *dev;
	int t_hlen;
	int mtu;
	int err;

	dev = __ip_tunnel_create(net, itn->rtnl_link_ops, parms);
	if (IS_ERR(dev))
		return ERR_CAST(dev);

	mtu = ip_tunnel_bind_dev(dev);
	err = dev_set_mtu(dev, mtu);
	if (err)
		goto err_dev_set_mtu;

	nt = netdev_priv(dev);
	t_hlen = nt->hlen + sizeof(struct iphdr);
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = IP_MAX_MTU - dev->hard_header_len - t_hlen;
	ip_tunnel_add(itn, nt);
	return nt;

err_dev_set_mtu:
	unregister_netdevice(dev);
	return ERR_PTR(err);
}