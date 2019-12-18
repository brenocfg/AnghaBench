#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int kill_prior_tuple; int xs_heap_continue; TYPE_2__* indexRelation; scalar_t__ xs_heapfetch; int /*<<< orphan*/  xs_snapshot; } ;
struct TYPE_7__ {TYPE_1__* rd_indam; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* amrestrpos ) (TYPE_3__*) ;} ;
typedef  TYPE_3__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_SCAN_PROCEDURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsMVCCSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CHECKS ; 
 int /*<<< orphan*/  amrestrpos ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  table_index_fetch_reset (scalar_t__) ; 

void
index_restrpos(IndexScanDesc scan)
{
	Assert(IsMVCCSnapshot(scan->xs_snapshot));

	SCAN_CHECKS;
	CHECK_SCAN_PROCEDURE(amrestrpos);

	/* release resources (like buffer pins) from table accesses */
	if (scan->xs_heapfetch)
		table_index_fetch_reset(scan->xs_heapfetch);

	scan->kill_prior_tuple = false; /* for safety */
	scan->xs_heap_continue = false;

	scan->indexRelation->rd_indam->amrestrpos(scan);
}