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
struct list_head {int dummy; } ;
struct ip6gre_net {struct net_device* fb_tunnel_dev; } ;

/* Variables and functions */
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  ip6gre_net_id ; 
 struct ip6gre_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 

__attribute__((used)) static void ip6gre_dellink(struct net_device *dev, struct list_head *head)
{
	struct net *net = dev_net(dev);
	struct ip6gre_net *ign = net_generic(net, ip6gre_net_id);

	if (dev != ign->fb_tunnel_dev)
		unregister_netdevice_queue(dev, head);
}