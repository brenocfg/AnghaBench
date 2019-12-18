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
typedef  scalar_t__ u32 ;
struct rt6_mtu_change_arg {scalar_t__ dev; scalar_t__ mtu; struct fib6_info* f6i; } ;
struct TYPE_2__ {scalar_t__ mtu6; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct fib6_nh {scalar_t__ fib_nh_dev; } ;
struct fib6_info {scalar_t__ fib6_pmtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAX_MTU ; 
 struct inet6_dev* __in6_dev_get (scalar_t__) ; 
 int /*<<< orphan*/  fib6_metric_set (struct fib6_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rt6_exception_lock ; 
 int /*<<< orphan*/  rt6_exceptions_update_pmtu (struct inet6_dev*,struct fib6_nh*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fib6_nh_mtu_change(struct fib6_nh *nh, void *_arg)
{
	struct rt6_mtu_change_arg *arg = (struct rt6_mtu_change_arg *)_arg;
	struct fib6_info *f6i = arg->f6i;

	/* For administrative MTU increase, there is no way to discover
	 * IPv6 PMTU increase, so PMTU increase should be updated here.
	 * Since RFC 1981 doesn't include administrative MTU increase
	 * update PMTU increase is a MUST. (i.e. jumbo frame)
	 */
	if (nh->fib_nh_dev == arg->dev) {
		struct inet6_dev *idev = __in6_dev_get(arg->dev);
		u32 mtu = f6i->fib6_pmtu;

		if (mtu >= arg->mtu ||
		    (mtu < arg->mtu && mtu == idev->cnf.mtu6))
			fib6_metric_set(f6i, RTAX_MTU, arg->mtu);

		spin_lock_bh(&rt6_exception_lock);
		rt6_exceptions_update_pmtu(idev, nh, arg->mtu);
		spin_unlock_bh(&rt6_exception_lock);
	}

	return 0;
}