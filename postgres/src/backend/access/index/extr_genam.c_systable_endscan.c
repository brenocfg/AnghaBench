#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ snapshot; int /*<<< orphan*/  scan; scalar_t__ irel; int /*<<< orphan*/  iscan; int /*<<< orphan*/ * slot; } ;
typedef  TYPE_1__* SysScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnregisterSnapshot (scalar_t__) ; 
 int /*<<< orphan*/  index_close (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 

void
systable_endscan(SysScanDesc sysscan)
{
	if (sysscan->slot)
	{
		ExecDropSingleTupleTableSlot(sysscan->slot);
		sysscan->slot = NULL;
	}

	if (sysscan->irel)
	{
		index_endscan(sysscan->iscan);
		index_close(sysscan->irel, AccessShareLock);
	}
	else
		table_endscan(sysscan->scan);

	if (sysscan->snapshot)
		UnregisterSnapshot(sysscan->snapshot);

	pfree(sysscan);
}