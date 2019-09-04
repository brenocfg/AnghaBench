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
struct netdev_adjacent {void* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  lower; } ;
struct net_device {TYPE_1__ adj_list; } ;

/* Variables and functions */
 struct netdev_adjacent* __netdev_find_adj (struct net_device*,int /*<<< orphan*/ *) ; 

void *netdev_lower_dev_get_private(struct net_device *dev,
				   struct net_device *lower_dev)
{
	struct netdev_adjacent *lower;

	if (!lower_dev)
		return NULL;
	lower = __netdev_find_adj(lower_dev, &dev->adj_list.lower);
	if (!lower)
		return NULL;

	return lower->private;
}