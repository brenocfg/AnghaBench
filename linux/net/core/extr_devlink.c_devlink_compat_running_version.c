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
struct devlink {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  info_get; } ;

/* Variables and functions */
 int /*<<< orphan*/  __devlink_compat_running_version (struct devlink*,char*,size_t) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct devlink* netdev_to_devlink (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void devlink_compat_running_version(struct net_device *dev,
				    char *buf, size_t len)
{
	struct devlink *devlink;

	dev_hold(dev);
	rtnl_unlock();

	devlink = netdev_to_devlink(dev);
	if (!devlink || !devlink->ops->info_get)
		goto out;

	mutex_lock(&devlink->lock);
	__devlink_compat_running_version(devlink, buf, len);
	mutex_unlock(&devlink->lock);

out:
	rtnl_lock();
	dev_put(dev);
}