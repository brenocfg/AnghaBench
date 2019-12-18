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
struct devlink {int /*<<< orphan*/  port_list; int /*<<< orphan*/  sb_list; int /*<<< orphan*/  dpipe_table_list; int /*<<< orphan*/  resource_list; int /*<<< orphan*/  param_list; int /*<<< orphan*/  region_list; int /*<<< orphan*/  reporter_list; int /*<<< orphan*/  trap_list; int /*<<< orphan*/  trap_group_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  reporters_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct devlink*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void devlink_free(struct devlink *devlink)
{
	mutex_destroy(&devlink->reporters_lock);
	mutex_destroy(&devlink->lock);
	WARN_ON(!list_empty(&devlink->trap_group_list));
	WARN_ON(!list_empty(&devlink->trap_list));
	WARN_ON(!list_empty(&devlink->reporter_list));
	WARN_ON(!list_empty(&devlink->region_list));
	WARN_ON(!list_empty(&devlink->param_list));
	WARN_ON(!list_empty(&devlink->resource_list));
	WARN_ON(!list_empty(&devlink->dpipe_table_list));
	WARN_ON(!list_empty(&devlink->sb_list));
	WARN_ON(!list_empty(&devlink->port_list));

	kfree(devlink);
}