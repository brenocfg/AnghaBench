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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ip_tunnel_net {struct net_device* fb_tunnel_dev; } ;
struct ip_tunnel {int /*<<< orphan*/  dst_cache; int /*<<< orphan*/  ip_tnl_net_id; struct net* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_cache_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_tunnel_del (struct ip_tunnel_net*,struct ip_tunnel*) ; 
 struct ip_tunnel_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

void ip_tunnel_uninit(struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct net *net = tunnel->net;
	struct ip_tunnel_net *itn;

	itn = net_generic(net, tunnel->ip_tnl_net_id);
	/* fb_tunnel_dev will be unregisted in net-exit call. */
	if (itn->fb_tunnel_dev != dev)
		ip_tunnel_del(itn, netdev_priv(dev));

	dst_cache_reset(&tunnel->dst_cache);
}