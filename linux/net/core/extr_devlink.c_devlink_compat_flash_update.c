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
struct TYPE_2__ {int (* flash_update ) (struct devlink*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct devlink* netdev_to_devlink (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int stub1 (struct devlink*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int devlink_compat_flash_update(struct net_device *dev, const char *file_name)
{
	struct devlink *devlink;
	int ret;

	dev_hold(dev);
	rtnl_unlock();

	devlink = netdev_to_devlink(dev);
	if (!devlink || !devlink->ops->flash_update) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	mutex_lock(&devlink->lock);
	ret = devlink->ops->flash_update(devlink, file_name, NULL, NULL);
	mutex_unlock(&devlink->lock);

out:
	rtnl_lock();
	dev_put(dev);

	return ret;
}