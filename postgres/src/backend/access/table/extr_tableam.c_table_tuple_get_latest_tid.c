#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TableScanDesc ;
struct TYPE_9__ {int /*<<< orphan*/  (* tuple_get_latest_tid ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* tuple_tid_valid ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ TableAmRoutine ;
struct TYPE_10__ {TYPE_2__* rd_tableam; } ;
struct TYPE_8__ {TYPE_3__* rs_rd; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumberNoCheck (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumberNoCheck (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
table_tuple_get_latest_tid(TableScanDesc scan, ItemPointer tid)
{
	Relation	rel = scan->rs_rd;
	const TableAmRoutine *tableam = rel->rd_tableam;

	/*
	 * Since this can be called with user-supplied TID, don't trust the input
	 * too much.
	 */
	if (!tableam->tuple_tid_valid(scan, tid))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("tid (%u, %u) is not valid for relation \"%s\"",
						ItemPointerGetBlockNumberNoCheck(tid),
						ItemPointerGetOffsetNumberNoCheck(tid),
						RelationGetRelationName(rel))));

	tableam->tuple_get_latest_tid(scan, tid);
}