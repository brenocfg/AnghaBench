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
struct net_device {int flags; } ;
struct TYPE_2__ {scalar_t__ disable_ipv6; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  EACCES ; 
 struct inet6_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int IFF_LOOPBACK ; 
 scalar_t__ IS_ERR (struct inet6_dev*) ; 
 int /*<<< orphan*/  addrconf_add_mroute (struct net_device*) ; 
 struct inet6_dev* ipv6_find_idev (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_l3_master (struct net_device*) ; 

__attribute__((used)) static struct inet6_dev *addrconf_add_dev(struct net_device *dev)
{
	struct inet6_dev *idev;

	ASSERT_RTNL();

	idev = ipv6_find_idev(dev);
	if (IS_ERR(idev))
		return idev;

	if (idev->cnf.disable_ipv6)
		return ERR_PTR(-EACCES);

	/* Add default multicast route */
	if (!(dev->flags & IFF_LOOPBACK) && !netif_is_l3_master(dev))
		addrconf_add_mroute(dev);

	return idev;
}