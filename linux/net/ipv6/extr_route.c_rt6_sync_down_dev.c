#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ skip_notify_on_dev_down; } ;
struct TYPE_6__ {TYPE_2__ sysctl; } ;
struct net {TYPE_3__ ipv6; } ;
struct TYPE_4__ {unsigned long event; } ;
struct arg_netdev_event {TYPE_1__ member_1; struct net_device* dev; } ;

/* Variables and functions */
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib6_clean_all (struct net*,int /*<<< orphan*/ ,struct arg_netdev_event*) ; 
 int /*<<< orphan*/  fib6_clean_all_skip_notify (struct net*,int /*<<< orphan*/ ,struct arg_netdev_event*) ; 
 int /*<<< orphan*/  fib6_ifdown ; 

void rt6_sync_down_dev(struct net_device *dev, unsigned long event)
{
	struct arg_netdev_event arg = {
		.dev = dev,
		{
			.event = event,
		},
	};
	struct net *net = dev_net(dev);

	if (net->ipv6.sysctl.skip_notify_on_dev_down)
		fib6_clean_all_skip_notify(net, fib6_ifdown, &arg);
	else
		fib6_clean_all(net, fib6_ifdown, &arg);
}