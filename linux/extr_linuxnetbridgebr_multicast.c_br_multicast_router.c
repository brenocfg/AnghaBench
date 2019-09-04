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
struct net_bridge {int /*<<< orphan*/  multicast_lock; } ;

/* Variables and functions */
 int br_multicast_is_router (struct net_bridge*) ; 
 struct net_bridge* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool br_multicast_router(const struct net_device *dev)
{
	struct net_bridge *br = netdev_priv(dev);
	bool is_router;

	spin_lock_bh(&br->multicast_lock);
	is_router = br_multicast_is_router(br);
	spin_unlock_bh(&br->multicast_lock);
	return is_router;
}