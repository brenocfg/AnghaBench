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
struct netdev_adjacent {int ignore; } ;
struct TYPE_2__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct net_device {TYPE_1__ adj_list; } ;

/* Variables and functions */
 struct netdev_adjacent* __netdev_find_adj (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __netdev_adjacent_dev_set(struct net_device *upper_dev,
				      struct net_device *lower_dev,
				      bool val)
{
	struct netdev_adjacent *adj;

	adj = __netdev_find_adj(lower_dev, &upper_dev->adj_list.lower);
	if (adj)
		adj->ignore = val;

	adj = __netdev_find_adj(upper_dev, &lower_dev->adj_list.upper);
	if (adj)
		adj->ignore = val;
}