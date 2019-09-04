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
 int /*<<< orphan*/  lockdep_set_class_and_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_get_nest_level (struct net_device*) ; 
 int /*<<< orphan*/  macvlan_netdev_addr_lock_key ; 
 int /*<<< orphan*/  netdev_lockdep_set_classes (struct net_device*) ; 

__attribute__((used)) static void macvlan_set_lockdep_class(struct net_device *dev)
{
	netdev_lockdep_set_classes(dev);
	lockdep_set_class_and_subclass(&dev->addr_list_lock,
				       &macvlan_netdev_addr_lock_key,
				       macvlan_get_nest_level(dev));
}