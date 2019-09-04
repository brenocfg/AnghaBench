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
typedef  void* u64 ;
struct devlink_dpipe_table {int resource_valid; void* resource_units; void* resource_id; } ;
struct devlink {int /*<<< orphan*/  lock; int /*<<< orphan*/  dpipe_table_list; } ;

/* Variables and functions */
 int EINVAL ; 
 struct devlink_dpipe_table* devlink_dpipe_table_find (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int devlink_dpipe_table_resource_set(struct devlink *devlink,
				     const char *table_name, u64 resource_id,
				     u64 resource_units)
{
	struct devlink_dpipe_table *table;
	int err = 0;

	mutex_lock(&devlink->lock);
	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name);
	if (!table) {
		err = -EINVAL;
		goto out;
	}
	table->resource_id = resource_id;
	table->resource_units = resource_units;
	table->resource_valid = true;
out:
	mutex_unlock(&devlink->lock);
	return err;
}