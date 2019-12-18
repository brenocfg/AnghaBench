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
 int /*<<< orphan*/  ____netdev_has_upper_dev ; 
 int /*<<< orphan*/  netdev_walk_all_upper_dev_rcu (struct net_device*,int /*<<< orphan*/ ,struct net_device*) ; 

bool netdev_has_upper_dev_all_rcu(struct net_device *dev,
				  struct net_device *upper_dev)
{
	return !!netdev_walk_all_upper_dev_rcu(dev, ____netdev_has_upper_dev,
					       upper_dev);
}