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
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENODEV ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int __ipv6_dev_mc_dec (struct inet6_dev*,struct in6_addr const*) ; 

int ipv6_dev_mc_dec(struct net_device *dev, const struct in6_addr *addr)
{
	struct inet6_dev *idev;
	int err;

	ASSERT_RTNL();

	idev = __in6_dev_get(dev);
	if (!idev)
		err = -ENODEV;
	else
		err = __ipv6_dev_mc_dec(idev, addr);

	return err;
}