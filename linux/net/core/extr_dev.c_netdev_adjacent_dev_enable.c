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
 int /*<<< orphan*/  __netdev_adjacent_dev_set (struct net_device*,struct net_device*,int) ; 

__attribute__((used)) static void netdev_adjacent_dev_enable(struct net_device *upper_dev,
				       struct net_device *lower_dev)
{
	__netdev_adjacent_dev_set(upper_dev, lower_dev, false);
}