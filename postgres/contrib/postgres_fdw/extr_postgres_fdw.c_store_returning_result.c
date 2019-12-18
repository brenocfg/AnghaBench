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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int /*<<< orphan*/  temp_cxt; int /*<<< orphan*/  retrieved_attrs; int /*<<< orphan*/  attinmeta; int /*<<< orphan*/  rel; } ;
typedef  TYPE_1__ PgFdwModifyState ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  ExecForceStoreHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_tuple_from_result_row (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_returning_result(PgFdwModifyState *fmstate,
					   TupleTableSlot *slot, PGresult *res)
{
	PG_TRY();
	{
		HeapTuple	newtup;

		newtup = make_tuple_from_result_row(res, 0,
											fmstate->rel,
											fmstate->attinmeta,
											fmstate->retrieved_attrs,
											NULL,
											fmstate->temp_cxt);

		/*
		 * The returning slot will not necessarily be suitable to store
		 * heaptuples directly, so allow for conversion.
		 */
		ExecForceStoreHeapTuple(newtup, slot, true);
	}
	PG_CATCH();
	{
		if (res)
			PQclear(res);
		PG_RE_THROW();
	}
	PG_END_TRY();
}