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
struct TYPE_2__ {struct list_head upper; } ;
struct net_device {TYPE_1__ adj_list; } ;

/* Variables and functions */
 struct net_device* netdev_next_upper_dev_rcu (struct net_device*,struct list_head**) ; 

int netdev_walk_all_upper_dev_rcu(struct net_device *dev,
				  int (*fn)(struct net_device *dev,
					    void *data),
				  void *data)
{
	struct net_device *udev;
	struct list_head *iter;
	int ret;

	for (iter = &dev->adj_list.upper,
	     udev = netdev_next_upper_dev_rcu(dev, &iter);
	     udev;
	     udev = netdev_next_upper_dev_rcu(dev, &iter)) {
		/* first is the upper device itself */
		ret = fn(udev, data);
		if (ret)
			return ret;

		/* then look at all of its upper devices */
		ret = netdev_walk_all_upper_dev_rcu(udev, fn, data);
		if (ret)
			return ret;
	}

	return 0;
}