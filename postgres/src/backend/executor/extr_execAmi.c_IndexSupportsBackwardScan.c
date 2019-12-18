#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  relam; } ;
struct TYPE_5__ {int amcanbackward; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ IndexAmRoutine ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetIndexAmRoutineByAmId (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static bool
IndexSupportsBackwardScan(Oid indexid)
{
	bool		result;
	HeapTuple	ht_idxrel;
	Form_pg_class idxrelrec;
	IndexAmRoutine *amroutine;

	/* Fetch the pg_class tuple of the index relation */
	ht_idxrel = SearchSysCache1(RELOID, ObjectIdGetDatum(indexid));
	if (!HeapTupleIsValid(ht_idxrel))
		elog(ERROR, "cache lookup failed for relation %u", indexid);
	idxrelrec = (Form_pg_class) GETSTRUCT(ht_idxrel);

	/* Fetch the index AM's API struct */
	amroutine = GetIndexAmRoutineByAmId(idxrelrec->relam, false);

	result = amroutine->amcanbackward;

	pfree(amroutine);
	ReleaseSysCache(ht_idxrel);

	return result;
}