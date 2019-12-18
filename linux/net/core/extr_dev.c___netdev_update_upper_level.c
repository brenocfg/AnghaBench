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
struct net_device {scalar_t__ upper_level; } ;

/* Variables and functions */
 scalar_t__ __netdev_upper_depth (struct net_device*) ; 

__attribute__((used)) static int __netdev_update_upper_level(struct net_device *dev, void *data)
{
	dev->upper_level = __netdev_upper_depth(dev) + 1;
	return 0;
}