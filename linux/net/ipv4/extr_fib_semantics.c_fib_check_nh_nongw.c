#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct in_device {TYPE_1__* dev; } ;
struct fib_nh {int fib_nh_flags; TYPE_1__* fib_nh_dev; int /*<<< orphan*/  fib_nh_scope; int /*<<< orphan*/  fib_nh_oif; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int ENODEV ; 
 int IFF_UP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int RTNH_F_LINKDOWN ; 
 int RTNH_F_ONLINK ; 
 int RTNH_F_PERVASIVE ; 
 int /*<<< orphan*/  RT_SCOPE_HOST ; 
 int /*<<< orphan*/  dev_hold (TYPE_1__*) ; 
 struct in_device* inetdev_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_ok (TYPE_1__*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int fib_check_nh_nongw(struct net *net, struct fib_nh *nh,
			      struct netlink_ext_ack *extack)
{
	struct in_device *in_dev;
	int err;

	if (nh->fib_nh_flags & (RTNH_F_PERVASIVE | RTNH_F_ONLINK)) {
		NL_SET_ERR_MSG(extack,
			       "Invalid flags for nexthop - PERVASIVE and ONLINK can not be set");
		return -EINVAL;
	}

	rcu_read_lock();

	err = -ENODEV;
	in_dev = inetdev_by_index(net, nh->fib_nh_oif);
	if (!in_dev)
		goto out;
	err = -ENETDOWN;
	if (!(in_dev->dev->flags & IFF_UP)) {
		NL_SET_ERR_MSG(extack, "Device for nexthop is not up");
		goto out;
	}

	nh->fib_nh_dev = in_dev->dev;
	dev_hold(nh->fib_nh_dev);
	nh->fib_nh_scope = RT_SCOPE_HOST;
	if (!netif_carrier_ok(nh->fib_nh_dev))
		nh->fib_nh_flags |= RTNH_F_LINKDOWN;
	err = 0;
out:
	rcu_read_unlock();
	return err;
}