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
struct fib6_nh {struct net_device const* fib_nh_dev; } ;

/* Variables and functions */

__attribute__((used)) static int fib6_info_nh_uses_dev(struct fib6_nh *nh, void *arg)
{
	const struct net_device *dev = arg;

	if (nh->fib_nh_dev == dev)
		return 1;

	return 0;
}