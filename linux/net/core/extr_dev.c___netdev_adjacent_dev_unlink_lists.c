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
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netdev_adjacent_dev_remove (struct net_device*,struct net_device*,int /*<<< orphan*/ ,struct list_head*) ; 

__attribute__((used)) static void __netdev_adjacent_dev_unlink_lists(struct net_device *dev,
					       struct net_device *upper_dev,
					       u16 ref_nr,
					       struct list_head *up_list,
					       struct list_head *down_list)
{
	__netdev_adjacent_dev_remove(dev, upper_dev, ref_nr, up_list);
	__netdev_adjacent_dev_remove(upper_dev, dev, ref_nr, down_list);
}