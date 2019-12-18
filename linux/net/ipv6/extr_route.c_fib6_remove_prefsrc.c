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
typedef  void net_device ;
struct TYPE_5__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_2__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct TYPE_6__ {scalar_t__ plen; int /*<<< orphan*/  addr; } ;
struct fib6_info {TYPE_3__ fib6_prefsrc; TYPE_1__* fib6_nh; int /*<<< orphan*/  nh; } ;
struct arg_dev_net_ip {struct in6_addr* addr; struct net* net; void* dev; } ;
struct TYPE_4__ {scalar_t__ fib_nh_dev; } ;

/* Variables and functions */
 scalar_t__ ipv6_addr_equal (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt6_exception_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fib6_remove_prefsrc(struct fib6_info *rt, void *arg)
{
	struct net_device *dev = ((struct arg_dev_net_ip *)arg)->dev;
	struct net *net = ((struct arg_dev_net_ip *)arg)->net;
	struct in6_addr *addr = ((struct arg_dev_net_ip *)arg)->addr;

	if (!rt->nh &&
	    ((void *)rt->fib6_nh->fib_nh_dev == dev || !dev) &&
	    rt != net->ipv6.fib6_null_entry &&
	    ipv6_addr_equal(addr, &rt->fib6_prefsrc.addr)) {
		spin_lock_bh(&rt6_exception_lock);
		/* remove prefsrc entry */
		rt->fib6_prefsrc.plen = 0;
		spin_unlock_bh(&rt6_exception_lock);
	}
	return 0;
}