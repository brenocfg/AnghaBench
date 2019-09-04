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
struct net_device {unsigned int flags; unsigned int gflags; scalar_t__ allmulti; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EOVERFLOW ; 
 unsigned int IFF_ALLMULTI ; 
 int /*<<< orphan*/  __dev_notify_flags (struct net_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_change_rx_flags (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  dev_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dev_set_allmulti(struct net_device *dev, int inc, bool notify)
{
	unsigned int old_flags = dev->flags, old_gflags = dev->gflags;

	ASSERT_RTNL();

	dev->flags |= IFF_ALLMULTI;
	dev->allmulti += inc;
	if (dev->allmulti == 0) {
		/*
		 * Avoid overflow.
		 * If inc causes overflow, untouch allmulti and return error.
		 */
		if (inc < 0)
			dev->flags &= ~IFF_ALLMULTI;
		else {
			dev->allmulti -= inc;
			pr_warn("%s: allmulti touches roof, set allmulti failed. allmulti feature of device might be broken.\n",
				dev->name);
			return -EOVERFLOW;
		}
	}
	if (dev->flags ^ old_flags) {
		dev_change_rx_flags(dev, IFF_ALLMULTI);
		dev_set_rx_mode(dev);
		if (notify)
			__dev_notify_flags(dev, old_flags,
					   dev->gflags ^ old_gflags);
	}
	return 0;
}