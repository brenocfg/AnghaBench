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
struct TYPE_10__ {int /*<<< orphan*/  items; scalar_t__ isDrop; int /*<<< orphan*/  opfamilyname; int /*<<< orphan*/  amname; } ;
struct TYPE_9__ {int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {int amstrategies; int amsupport; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ IndexAmRoutine ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_am ;
typedef  TYPE_3__ AlterOpFamilyStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AMNAME ; 
 int /*<<< orphan*/  AlterOpFamilyAdd (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AlterOpFamilyDrop (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetIndexAmRoutineByAmId (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int SHRT_MAX ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_opfamily_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  superuser () ; 

Oid
AlterOpFamily(AlterOpFamilyStmt *stmt)
{
	Oid			amoid,			/* our AM's oid */
				opfamilyoid;	/* oid of opfamily */
	int			maxOpNumber,	/* amstrategies value */
				maxProcNumber;	/* amsupport value */
	HeapTuple	tup;
	Form_pg_am	amform;
	IndexAmRoutine *amroutine;

	/* Get necessary info about access method */
	tup = SearchSysCache1(AMNAME, CStringGetDatum(stmt->amname));
	if (!HeapTupleIsValid(tup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("access method \"%s\" does not exist",
						stmt->amname)));

	amform = (Form_pg_am) GETSTRUCT(tup);
	amoid = amform->oid;
	amroutine = GetIndexAmRoutineByAmId(amoid, false);
	ReleaseSysCache(tup);

	maxOpNumber = amroutine->amstrategies;
	/* if amstrategies is zero, just enforce that op numbers fit in int16 */
	if (maxOpNumber <= 0)
		maxOpNumber = SHRT_MAX;
	maxProcNumber = amroutine->amsupport;

	/* XXX Should we make any privilege check against the AM? */

	/* Look up the opfamily */
	opfamilyoid = get_opfamily_oid(amoid, stmt->opfamilyname, false);

	/*
	 * Currently, we require superuser privileges to alter an opfamily.
	 *
	 * XXX re-enable NOT_USED code sections below if you remove this test.
	 */
	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("must be superuser to alter an operator family")));

	/*
	 * ADD and DROP cases need separate code from here on down.
	 */
	if (stmt->isDrop)
		AlterOpFamilyDrop(stmt, amoid, opfamilyoid,
						  maxOpNumber, maxProcNumber, stmt->items);
	else
		AlterOpFamilyAdd(stmt, amoid, opfamilyoid,
						 maxOpNumber, maxProcNumber, stmt->items);

	return opfamilyoid;
}