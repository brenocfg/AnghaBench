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
struct vport {int dummy; } ;
struct net_device {int /*<<< orphan*/  rx_handler_data; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_is_ovs_port (struct net_device*) ; 
 scalar_t__ rcu_dereference_rtnl (int /*<<< orphan*/ ) ; 

struct vport *ovs_netdev_get_vport(struct net_device *dev)
{
	if (likely(netif_is_ovs_port(dev)))
		return (struct vport *)
			rcu_dereference_rtnl(dev->rx_handler_data);
	else
		return NULL;
}