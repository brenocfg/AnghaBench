#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_11__ {scalar_t__ phs_relid; int phs_snapshot_off; int /*<<< orphan*/  phs_snapshot_any; } ;
struct TYPE_10__ {TYPE_1__* rd_tableam; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* scan_begin ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int) ;} ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* ParallelTableScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  RegisterSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  RestoreSnapshot (char*) ; 
 int SO_ALLOW_PAGEMODE ; 
 int SO_ALLOW_STRAT ; 
 int SO_ALLOW_SYNC ; 
 int SO_TEMP_SNAPSHOT ; 
 int SO_TYPE_SEQSCAN ; 
 int /*<<< orphan*/  SnapshotAny ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int) ; 

TableScanDesc
table_beginscan_parallel(Relation relation, ParallelTableScanDesc parallel_scan)
{
	Snapshot	snapshot;
	uint32		flags = SO_TYPE_SEQSCAN |
	SO_ALLOW_STRAT | SO_ALLOW_SYNC | SO_ALLOW_PAGEMODE;

	Assert(RelationGetRelid(relation) == parallel_scan->phs_relid);

	if (!parallel_scan->phs_snapshot_any)
	{
		/* Snapshot was serialized -- restore it */
		snapshot = RestoreSnapshot((char *) parallel_scan +
								   parallel_scan->phs_snapshot_off);
		RegisterSnapshot(snapshot);
		flags |= SO_TEMP_SNAPSHOT;
	}
	else
	{
		/* SnapshotAny passed by caller (not serialized) */
		snapshot = SnapshotAny;
	}

	return relation->rd_tableam->scan_begin(relation, snapshot, 0, NULL,
											parallel_scan, flags);
}