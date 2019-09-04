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
struct net_device {int dummy; } ;
struct TYPE_2__ {unsigned long event; } ;
struct arg_netdev_event {TYPE_1__ member_1; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib6_clean_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arg_netdev_event*) ; 
 int /*<<< orphan*/  fib6_ifdown ; 

void rt6_sync_down_dev(struct net_device *dev, unsigned long event)
{
	struct arg_netdev_event arg = {
		.dev = dev,
		{
			.event = event,
		},
	};

	fib6_clean_all(dev_net(dev), fib6_ifdown, &arg);
}