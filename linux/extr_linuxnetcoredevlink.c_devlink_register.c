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
struct devlink {int /*<<< orphan*/  list; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_NEW ; 
 int /*<<< orphan*/  devlink_list ; 
 int /*<<< orphan*/  devlink_mutex ; 
 int /*<<< orphan*/  devlink_notify (struct devlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int devlink_register(struct devlink *devlink, struct device *dev)
{
	mutex_lock(&devlink_mutex);
	devlink->dev = dev;
	list_add_tail(&devlink->list, &devlink_list);
	devlink_notify(devlink, DEVLINK_CMD_NEW);
	mutex_unlock(&devlink_mutex);
	return 0;
}