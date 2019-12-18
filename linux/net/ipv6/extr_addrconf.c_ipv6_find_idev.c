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
struct net_device {int flags; } ;
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int IFF_UP ; 
 scalar_t__ IS_ERR (struct inet6_dev*) ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 struct inet6_dev* ipv6_add_dev (struct net_device*) ; 
 int /*<<< orphan*/  ipv6_mc_up (struct inet6_dev*) ; 

__attribute__((used)) static struct inet6_dev *ipv6_find_idev(struct net_device *dev)
{
	struct inet6_dev *idev;

	ASSERT_RTNL();

	idev = __in6_dev_get(dev);
	if (!idev) {
		idev = ipv6_add_dev(dev);
		if (IS_ERR(idev))
			return idev;
	}

	if (dev->flags&IFF_UP)
		ipv6_mc_up(idev);
	return idev;
}