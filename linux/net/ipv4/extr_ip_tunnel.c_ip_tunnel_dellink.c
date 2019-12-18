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
struct list_head {int dummy; } ;
struct ip_tunnel_net {struct net_device* fb_tunnel_dev; } ;
struct ip_tunnel {int /*<<< orphan*/  ip_tnl_net_id; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_tunnel_del (struct ip_tunnel_net*,struct ip_tunnel*) ; 
 struct ip_tunnel_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 

void ip_tunnel_dellink(struct net_device *dev, struct list_head *head)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct ip_tunnel_net *itn;

	itn = net_generic(tunnel->net, tunnel->ip_tnl_net_id);

	if (itn->fb_tunnel_dev != dev) {
		ip_tunnel_del(itn, netdev_priv(dev));
		unregister_netdevice_queue(dev, head);
	}
}