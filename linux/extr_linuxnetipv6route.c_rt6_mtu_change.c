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
struct rt6_mtu_change_arg {unsigned int mtu; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib6_clean_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rt6_mtu_change_arg*) ; 
 int /*<<< orphan*/  rt6_mtu_change_route ; 

void rt6_mtu_change(struct net_device *dev, unsigned int mtu)
{
	struct rt6_mtu_change_arg arg = {
		.dev = dev,
		.mtu = mtu,
	};

	fib6_clean_all(dev_net(dev), rt6_mtu_change_route, &arg);
}