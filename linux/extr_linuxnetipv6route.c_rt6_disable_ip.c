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
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  nd_tbl ; 
 int /*<<< orphan*/  neigh_ifdown (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  rt6_sync_down_dev (struct net_device*,unsigned long) ; 
 int /*<<< orphan*/  rt6_uncached_list_flush_dev (int /*<<< orphan*/ ,struct net_device*) ; 

void rt6_disable_ip(struct net_device *dev, unsigned long event)
{
	rt6_sync_down_dev(dev, event);
	rt6_uncached_list_flush_dev(dev_net(dev), dev);
	neigh_ifdown(&nd_tbl, dev);
}