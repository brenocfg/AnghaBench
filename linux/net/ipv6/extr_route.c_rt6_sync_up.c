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
struct TYPE_2__ {unsigned char nh_flags; } ;
struct arg_netdev_event {int /*<<< orphan*/  nh_flags; TYPE_1__ member_1; struct net_device* dev; } ;

/* Variables and functions */
 unsigned char RTNH_F_DEAD ; 
 int /*<<< orphan*/  RTNH_F_LINKDOWN ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib6_clean_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arg_netdev_event*) ; 
 int /*<<< orphan*/  fib6_ifup ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

void rt6_sync_up(struct net_device *dev, unsigned char nh_flags)
{
	struct arg_netdev_event arg = {
		.dev = dev,
		{
			.nh_flags = nh_flags,
		},
	};

	if (nh_flags & RTNH_F_DEAD && netif_carrier_ok(dev))
		arg.nh_flags |= RTNH_F_LINKDOWN;

	fib6_clean_all(dev_net(dev), fib6_ifup, &arg);
}