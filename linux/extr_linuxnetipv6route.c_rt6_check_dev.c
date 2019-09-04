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
struct net_device {int ifindex; } ;
struct TYPE_2__ {struct net_device* nh_dev; } ;
struct fib6_info {TYPE_1__ fib6_nh; } ;

/* Variables and functions */

__attribute__((used)) static inline int rt6_check_dev(struct fib6_info *rt, int oif)
{
	const struct net_device *dev = rt->fib6_nh.nh_dev;

	if (!oif || dev->ifindex == oif)
		return 2;
	return 0;
}