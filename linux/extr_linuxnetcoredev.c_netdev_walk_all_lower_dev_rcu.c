#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_2__ {struct list_head lower; } ;
struct net_device {TYPE_1__ adj_list; } ;

/* Variables and functions */
 struct net_device* netdev_next_lower_dev_rcu (struct net_device*,struct list_head**) ; 

int netdev_walk_all_lower_dev_rcu(struct net_device *dev,
				  int (*fn)(struct net_device *dev,
					    void *data),
				  void *data)
{
	struct net_device *ldev;
	struct list_head *iter;
	int ret;

	for (iter = &dev->adj_list.lower,
	     ldev = netdev_next_lower_dev_rcu(dev, &iter);
	     ldev;
	     ldev = netdev_next_lower_dev_rcu(dev, &iter)) {
		/* first is the lower device itself */
		ret = fn(ldev, data);
		if (ret)
			return ret;

		/* then look at all of its lower devices */
		ret = netdev_walk_all_lower_dev_rcu(ldev, fn, data);
		if (ret)
			return ret;
	}

	return 0;
}