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
 int /*<<< orphan*/  netdev_adjacent_dev_enable (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 

void netdev_adjacent_change_commit(struct net_device *old_dev,
				   struct net_device *new_dev,
				   struct net_device *dev)
{
	if (!new_dev || !old_dev)
		return;

	if (new_dev == old_dev)
		return;

	netdev_adjacent_dev_enable(dev, old_dev);
	netdev_upper_dev_unlink(old_dev, dev);
}