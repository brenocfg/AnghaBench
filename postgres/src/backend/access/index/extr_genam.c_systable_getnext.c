#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ xs_recheck; } ;
struct TYPE_4__ {int /*<<< orphan*/  slot; int /*<<< orphan*/  scan; TYPE_3__* iscan; scalar_t__ irel; } ;
typedef  TYPE_1__* SysScanDesc ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * ExecFetchSlotHeapTuple (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ index_getnext_slot (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ table_scan_getnextslot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HeapTuple
systable_getnext(SysScanDesc sysscan)
{
	HeapTuple	htup = NULL;

	if (sysscan->irel)
	{
		if (index_getnext_slot(sysscan->iscan, ForwardScanDirection, sysscan->slot))
		{
			bool		shouldFree;

			htup = ExecFetchSlotHeapTuple(sysscan->slot, false, &shouldFree);
			Assert(!shouldFree);

			/*
			 * We currently don't need to support lossy index operators for
			 * any system catalog scan.  It could be done here, using the scan
			 * keys to drive the operator calls, if we arranged to save the
			 * heap attnums during systable_beginscan(); this is practical
			 * because we still wouldn't need to support indexes on
			 * expressions.
			 */
			if (sysscan->iscan->xs_recheck)
				elog(ERROR, "system catalog scans with lossy index conditions are not implemented");
		}
	}
	else
	{
		if (table_scan_getnextslot(sysscan->scan, ForwardScanDirection, sysscan->slot))
		{
			bool		shouldFree;

			htup = ExecFetchSlotHeapTuple(sysscan->slot, false, &shouldFree);
			Assert(!shouldFree);
		}
	}

	return htup;
}