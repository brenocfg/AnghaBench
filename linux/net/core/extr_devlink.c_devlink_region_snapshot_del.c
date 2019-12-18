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
struct devlink_snapshot {int /*<<< orphan*/  data; int /*<<< orphan*/  (* data_destructor ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  list; } ;
struct devlink_region {int /*<<< orphan*/  cur_snapshots; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_REGION_DEL ; 
 int /*<<< orphan*/  devlink_nl_region_notify (struct devlink_region*,struct devlink_snapshot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct devlink_snapshot*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devlink_region_snapshot_del(struct devlink_region *region,
					struct devlink_snapshot *snapshot)
{
	devlink_nl_region_notify(region, snapshot, DEVLINK_CMD_REGION_DEL);
	region->cur_snapshots--;
	list_del(&snapshot->list);
	(*snapshot->data_destructor)(snapshot->data);
	kfree(snapshot);
}