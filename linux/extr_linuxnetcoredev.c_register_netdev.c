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

/* Variables and functions */
 int EINTR ; 
 int register_netdevice (struct net_device*) ; 
 scalar_t__ rtnl_lock_killable () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int register_netdev(struct net_device *dev)
{
	int err;

	if (rtnl_lock_killable())
		return -EINTR;
	err = register_netdevice(dev);
	rtnl_unlock();
	return err;
}