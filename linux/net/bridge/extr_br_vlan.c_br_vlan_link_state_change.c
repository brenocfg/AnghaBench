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
struct net_bridge {int dummy; } ;
struct br_vlan_link_state_walk_data {struct net_bridge* br; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_vlan_link_state_change_fn ; 
 int /*<<< orphan*/  netdev_walk_all_upper_dev_rcu (struct net_device*,int /*<<< orphan*/ ,struct br_vlan_link_state_walk_data*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void br_vlan_link_state_change(struct net_device *dev,
				      struct net_bridge *br)
{
	struct br_vlan_link_state_walk_data data = {
		.br = br
	};

	rcu_read_lock();
	netdev_walk_all_upper_dev_rcu(dev, br_vlan_link_state_change_fn,
				      &data);
	rcu_read_unlock();
}