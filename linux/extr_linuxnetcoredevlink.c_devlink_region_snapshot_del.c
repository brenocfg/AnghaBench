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
struct devlink_snapshot {int /*<<< orphan*/  data; int /*<<< orphan*/  (* data_destructor ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  list; TYPE_1__* region; } ;
struct TYPE_2__ {int /*<<< orphan*/  cur_snapshots; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct devlink_snapshot*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devlink_region_snapshot_del(struct devlink_snapshot *snapshot)
{
	snapshot->region->cur_snapshots--;
	list_del(&snapshot->list);
	(*snapshot->data_destructor)(snapshot->data);
	kfree(snapshot);
}