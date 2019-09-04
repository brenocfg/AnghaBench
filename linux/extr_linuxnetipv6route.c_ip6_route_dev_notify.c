#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {int flags; scalar_t__ reg_state; } ;
struct TYPE_10__ {TYPE_4__* ip6_null_entry; TYPE_2__* fib6_null_entry; } ;
struct net {TYPE_5__ ipv6; } ;
struct TYPE_8__ {struct net_device* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  rt6i_idev; TYPE_3__ dst; } ;
struct TYPE_6__ {struct net_device* nh_dev; } ;
struct TYPE_7__ {TYPE_1__ fib6_nh; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 unsigned long NETDEV_REGISTER ; 
 unsigned long NETDEV_UNREGISTER ; 
 scalar_t__ NETREG_UNREGISTERED ; 
 int NOTIFY_OK ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put_clear (int /*<<< orphan*/ *) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int ip6_route_dev_notify(struct notifier_block *this,
				unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct net *net = dev_net(dev);

	if (!(dev->flags & IFF_LOOPBACK))
		return NOTIFY_OK;

	if (event == NETDEV_REGISTER) {
		net->ipv6.fib6_null_entry->fib6_nh.nh_dev = dev;
		net->ipv6.ip6_null_entry->dst.dev = dev;
		net->ipv6.ip6_null_entry->rt6i_idev = in6_dev_get(dev);
#ifdef CONFIG_IPV6_MULTIPLE_TABLES
		net->ipv6.ip6_prohibit_entry->dst.dev = dev;
		net->ipv6.ip6_prohibit_entry->rt6i_idev = in6_dev_get(dev);
		net->ipv6.ip6_blk_hole_entry->dst.dev = dev;
		net->ipv6.ip6_blk_hole_entry->rt6i_idev = in6_dev_get(dev);
#endif
	 } else if (event == NETDEV_UNREGISTER &&
		    dev->reg_state != NETREG_UNREGISTERED) {
		/* NETDEV_UNREGISTER could be fired for multiple times by
		 * netdev_wait_allrefs(). Make sure we only call this once.
		 */
		in6_dev_put_clear(&net->ipv6.ip6_null_entry->rt6i_idev);
#ifdef CONFIG_IPV6_MULTIPLE_TABLES
		in6_dev_put_clear(&net->ipv6.ip6_prohibit_entry->rt6i_idev);
		in6_dev_put_clear(&net->ipv6.ip6_blk_hole_entry->rt6i_idev);
#endif
	}

	return NOTIFY_OK;
}