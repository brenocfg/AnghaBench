#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct fib6_result {int fib6_flags; TYPE_3__* f6i; TYPE_1__* nh; } ;
struct TYPE_8__ {struct net_device* loopback_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {TYPE_2__ fib6_dst; } ;
struct TYPE_5__ {struct net_device* fib_nh_dev; } ;

/* Variables and functions */
 int RTF_ANYCAST ; 
 int RTF_LOCAL ; 
 TYPE_4__* dev_net (struct net_device*) ; 
 struct net_device* l3mdev_master_dev_rcu (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_l3_master (struct net_device*) ; 
 scalar_t__ netif_is_l3_slave (struct net_device*) ; 
 int /*<<< orphan*/  rt6_need_strict (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device *ip6_rt_get_dev_rcu(const struct fib6_result *res)
{
	struct net_device *dev = res->nh->fib_nh_dev;

	if (res->fib6_flags & (RTF_LOCAL | RTF_ANYCAST)) {
		/* for copies of local routes, dst->dev needs to be the
		 * device if it is a master device, the master device if
		 * device is enslaved, and the loopback as the default
		 */
		if (netif_is_l3_slave(dev) &&
		    !rt6_need_strict(&res->f6i->fib6_dst.addr))
			dev = l3mdev_master_dev_rcu(dev);
		else if (!netif_is_l3_master(dev))
			dev = dev_net(dev)->loopback_dev;
		/* last case is netif_is_l3_master(dev) is true in which
		 * case we want dev returned to be dev
		 */
	}

	return dev;
}