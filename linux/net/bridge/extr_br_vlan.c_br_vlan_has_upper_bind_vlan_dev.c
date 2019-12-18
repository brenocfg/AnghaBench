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

/* Variables and functions */
 int /*<<< orphan*/  br_vlan_is_bind_vlan_dev_fn ; 
 int netdev_walk_all_upper_dev_rcu (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool br_vlan_has_upper_bind_vlan_dev(struct net_device *dev)
{
	int found;

	rcu_read_lock();
	found = netdev_walk_all_upper_dev_rcu(dev, br_vlan_is_bind_vlan_dev_fn,
					      NULL);
	rcu_read_unlock();

	return !!found;
}