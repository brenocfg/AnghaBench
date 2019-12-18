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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct br_vlan_bind_walk_data {struct net_device* result; int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_vlan_match_bind_vlan_dev_fn ; 
 int /*<<< orphan*/  netdev_walk_all_upper_dev_rcu (struct net_device*,int /*<<< orphan*/ ,struct br_vlan_bind_walk_data*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct net_device *
br_vlan_get_upper_bind_vlan_dev(struct net_device *dev, u16 vid)
{
	struct br_vlan_bind_walk_data data = {
		.vid = vid,
	};

	rcu_read_lock();
	netdev_walk_all_upper_dev_rcu(dev, br_vlan_match_bind_vlan_dev_fn,
				      &data);
	rcu_read_unlock();

	return data.result;
}