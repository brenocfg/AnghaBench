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
struct devlink {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_DEL ; 
 int /*<<< orphan*/  devlink_mutex ; 
 int /*<<< orphan*/  devlink_notify (struct devlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void devlink_unregister(struct devlink *devlink)
{
	mutex_lock(&devlink_mutex);
	devlink_notify(devlink, DEVLINK_CMD_DEL);
	list_del(&devlink->list);
	mutex_unlock(&devlink_mutex);
}