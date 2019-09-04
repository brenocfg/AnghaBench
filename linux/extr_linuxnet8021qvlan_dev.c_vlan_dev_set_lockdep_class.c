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
struct net_device {int /*<<< orphan*/  addr_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_set_class_and_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_for_each_tx_queue (struct net_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vlan_dev_set_lockdep_one ; 
 int /*<<< orphan*/  vlan_netdev_addr_lock_key ; 

__attribute__((used)) static void vlan_dev_set_lockdep_class(struct net_device *dev, int subclass)
{
	lockdep_set_class_and_subclass(&dev->addr_list_lock,
				       &vlan_netdev_addr_lock_key,
				       subclass);
	netdev_for_each_tx_queue(dev, vlan_dev_set_lockdep_one, &subclass);
}