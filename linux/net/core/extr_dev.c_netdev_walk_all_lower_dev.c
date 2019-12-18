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
 int /*<<< orphan*/  MAX_NEST_DEV ; 
 struct net_device* netdev_next_lower_dev (struct net_device*,struct list_head**) ; 

int netdev_walk_all_lower_dev(struct net_device *dev,
			      int (*fn)(struct net_device *dev,
					void *data),
			      void *data)
{
	struct net_device *ldev, *next, *now, *dev_stack[MAX_NEST_DEV + 1];
	struct list_head *niter, *iter, *iter_stack[MAX_NEST_DEV + 1];
	int ret, cur = 0;

	now = dev;
	iter = &dev->adj_list.lower;

	while (1) {
		if (now != dev) {
			ret = fn(now, data);
			if (ret)
				return ret;
		}

		next = NULL;
		while (1) {
			ldev = netdev_next_lower_dev(now, &iter);
			if (!ldev)
				break;

			next = ldev;
			niter = &ldev->adj_list.lower;
			dev_stack[cur] = now;
			iter_stack[cur++] = iter;
			break;
		}

		if (!next) {
			if (!cur)
				return 0;
			next = dev_stack[--cur];
			niter = iter_stack[cur];
		}

		now = next;
		iter = niter;
	}

	return 0;
}