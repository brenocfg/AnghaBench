#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* as_snap; } ;
struct TYPE_3__ {int active_count; scalar_t__ regd_count; scalar_t__ curcid; } ;
typedef  scalar_t__ CommandId ;

/* Variables and functions */
 TYPE_2__* ActiveSnapshot ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetCurrentCommandId (int) ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
UpdateActiveSnapshotCommandId(void)
{
	CommandId	save_curcid,
				curcid;

	Assert(ActiveSnapshot != NULL);
	Assert(ActiveSnapshot->as_snap->active_count == 1);
	Assert(ActiveSnapshot->as_snap->regd_count == 0);

	/*
	 * Don't allow modification of the active snapshot during parallel
	 * operation.  We share the snapshot to worker backends at the beginning
	 * of parallel operation, so any change to the snapshot can lead to
	 * inconsistencies.  We have other defenses against
	 * CommandCounterIncrement, but there are a few places that call this
	 * directly, so we put an additional guard here.
	 */
	save_curcid = ActiveSnapshot->as_snap->curcid;
	curcid = GetCurrentCommandId(false);
	if (IsInParallelMode() && save_curcid != curcid)
		elog(ERROR, "cannot modify commandid in active snapshot during a parallel operation");
	ActiveSnapshot->as_snap->curcid = curcid;
}