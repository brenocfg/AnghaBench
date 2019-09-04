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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct devlink_region {char const* name; int /*<<< orphan*/  list; int /*<<< orphan*/  snapshot_list; int /*<<< orphan*/  size; int /*<<< orphan*/  max_snapshots; struct devlink* devlink; } ;
struct devlink {int /*<<< orphan*/  lock; int /*<<< orphan*/  region_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_REGION_NEW ; 
 int EEXIST ; 
 int ENOMEM ; 
 struct devlink_region* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_nl_region_notify (struct devlink_region*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ devlink_region_get_by_name (struct devlink*,char const*) ; 
 struct devlink_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct devlink_region *devlink_region_create(struct devlink *devlink,
					     const char *region_name,
					     u32 region_max_snapshots,
					     u64 region_size)
{
	struct devlink_region *region;
	int err = 0;

	mutex_lock(&devlink->lock);

	if (devlink_region_get_by_name(devlink, region_name)) {
		err = -EEXIST;
		goto unlock;
	}

	region = kzalloc(sizeof(*region), GFP_KERNEL);
	if (!region) {
		err = -ENOMEM;
		goto unlock;
	}

	region->devlink = devlink;
	region->max_snapshots = region_max_snapshots;
	region->name = region_name;
	region->size = region_size;
	INIT_LIST_HEAD(&region->snapshot_list);
	list_add_tail(&region->list, &devlink->region_list);
	devlink_nl_region_notify(region, NULL, DEVLINK_CMD_REGION_NEW);

	mutex_unlock(&devlink->lock);
	return region;

unlock:
	mutex_unlock(&devlink->lock);
	return ERR_PTR(err);
}