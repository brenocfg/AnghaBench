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
struct ipvtap_dev {int /*<<< orphan*/  tap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipvlan_link_delete (struct net_device*,struct list_head*) ; 
 struct ipvtap_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 
 int /*<<< orphan*/  tap_del_queues (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipvtap_dellink(struct net_device *dev,
			   struct list_head *head)
{
	struct ipvtap_dev *vlan = netdev_priv(dev);

	netdev_rx_handler_unregister(dev);
	tap_del_queues(&vlan->tap);
	ipvlan_link_delete(dev, head);
}