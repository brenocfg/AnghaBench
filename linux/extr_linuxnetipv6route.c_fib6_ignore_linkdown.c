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
struct TYPE_2__ {int /*<<< orphan*/  ignore_routes_with_linkdown; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 struct inet6_dev* __in6_dev_get (struct net_device const*) ; 
 struct net_device* fib6_info_nh_dev (struct fib6_info const*) ; 

__attribute__((used)) static inline bool fib6_ignore_linkdown(const struct fib6_info *f6i)
{
	const struct net_device *dev = fib6_info_nh_dev(f6i);
	bool rc = false;

	if (dev) {
		const struct inet6_dev *idev = __in6_dev_get(dev);

		rc = !!idev->cnf.ignore_routes_with_linkdown;
	}

	return rc;
}