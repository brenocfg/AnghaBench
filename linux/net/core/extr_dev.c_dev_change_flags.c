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
struct netlink_ext_ack {int dummy; } ;
struct net_device {unsigned int flags; unsigned int gflags; } ;

/* Variables and functions */
 int __dev_change_flags (struct net_device*,unsigned int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  __dev_notify_flags (struct net_device*,unsigned int,unsigned int) ; 

int dev_change_flags(struct net_device *dev, unsigned int flags,
		     struct netlink_ext_ack *extack)
{
	int ret;
	unsigned int changes, old_flags = dev->flags, old_gflags = dev->gflags;

	ret = __dev_change_flags(dev, flags, extack);
	if (ret < 0)
		return ret;

	changes = (old_flags ^ dev->flags) | (old_gflags ^ dev->gflags);
	__dev_notify_flags(dev, old_flags, changes);
	return ret;
}