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
struct devlink_sb {int /*<<< orphan*/  list; } ;
struct devlink {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct devlink_sb* devlink_sb_get_by_index (struct devlink*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct devlink_sb*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void devlink_sb_unregister(struct devlink *devlink, unsigned int sb_index)
{
	struct devlink_sb *devlink_sb;

	mutex_lock(&devlink->lock);
	devlink_sb = devlink_sb_get_by_index(devlink, sb_index);
	WARN_ON(!devlink_sb);
	list_del(&devlink_sb->list);
	mutex_unlock(&devlink->lock);
	kfree(devlink_sb);
}