#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  slot; int /*<<< orphan*/  heap_rel; } ;
typedef  TYPE_1__* SysScanDesc ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  scalar_t__ HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ ExecFetchSlotHeapTuple (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCatalogSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int table_tuple_satisfies_snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
systable_recheck_tuple(SysScanDesc sysscan, HeapTuple tup)
{
	Snapshot	freshsnap;
	bool		result;

	Assert(tup == ExecFetchSlotHeapTuple(sysscan->slot, false, NULL));

	/*
	 * Trust that table_tuple_satisfies_snapshot() and its subsidiaries
	 * (commonly LockBuffer() and HeapTupleSatisfiesMVCC()) do not themselves
	 * acquire snapshots, so we need not register the snapshot.  Those
	 * facilities are too low-level to have any business scanning tables.
	 */
	freshsnap = GetCatalogSnapshot(RelationGetRelid(sysscan->heap_rel));

	result = table_tuple_satisfies_snapshot(sysscan->heap_rel,
											sysscan->slot,
											freshsnap);

	return result;
}