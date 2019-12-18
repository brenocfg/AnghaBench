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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct devlink_snapshot {int /*<<< orphan*/  list; int /*<<< orphan*/ * data_destructor; int /*<<< orphan*/ * data; struct devlink_region* region; int /*<<< orphan*/  id; } ;
struct devlink_region {scalar_t__ cur_snapshots; scalar_t__ max_snapshots; int /*<<< orphan*/  snapshot_list; struct devlink* devlink; } ;
struct devlink {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  devlink_snapshot_data_dest_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_REGION_NEW ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devlink_nl_region_notify (struct devlink_region*,struct devlink_snapshot*,int /*<<< orphan*/ ) ; 
 scalar_t__ devlink_region_snapshot_get_by_id (struct devlink_region*,int /*<<< orphan*/ ) ; 
 struct devlink_snapshot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int devlink_region_snapshot_create(struct devlink_region *region,
				   u8 *data, u32 snapshot_id,
				   devlink_snapshot_data_dest_t *data_destructor)
{
	struct devlink *devlink = region->devlink;
	struct devlink_snapshot *snapshot;
	int err;

	mutex_lock(&devlink->lock);

	/* check if region can hold one more snapshot */
	if (region->cur_snapshots == region->max_snapshots) {
		err = -ENOMEM;
		goto unlock;
	}

	if (devlink_region_snapshot_get_by_id(region, snapshot_id)) {
		err = -EEXIST;
		goto unlock;
	}

	snapshot = kzalloc(sizeof(*snapshot), GFP_KERNEL);
	if (!snapshot) {
		err = -ENOMEM;
		goto unlock;
	}

	snapshot->id = snapshot_id;
	snapshot->region = region;
	snapshot->data = data;
	snapshot->data_destructor = data_destructor;

	list_add_tail(&snapshot->list, &region->snapshot_list);

	region->cur_snapshots++;

	devlink_nl_region_notify(region, snapshot, DEVLINK_CMD_REGION_NEW);
	mutex_unlock(&devlink->lock);
	return 0;

unlock:
	mutex_unlock(&devlink->lock);
	return err;
}