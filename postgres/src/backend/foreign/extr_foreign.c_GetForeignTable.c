#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  options; int /*<<< orphan*/  serverid; int /*<<< orphan*/  relid; } ;
struct TYPE_4__ {int /*<<< orphan*/  ftserver; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_foreign_table ;
typedef  TYPE_2__ ForeignTable ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_foreign_table_ftoptions ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FOREIGNTABLEREL ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  untransformRelOptions (int /*<<< orphan*/ ) ; 

ForeignTable *
GetForeignTable(Oid relid)
{
	Form_pg_foreign_table tableform;
	ForeignTable *ft;
	HeapTuple	tp;
	Datum		datum;
	bool		isnull;

	tp = SearchSysCache1(FOREIGNTABLEREL, ObjectIdGetDatum(relid));
	if (!HeapTupleIsValid(tp))
		elog(ERROR, "cache lookup failed for foreign table %u", relid);
	tableform = (Form_pg_foreign_table) GETSTRUCT(tp);

	ft = (ForeignTable *) palloc(sizeof(ForeignTable));
	ft->relid = relid;
	ft->serverid = tableform->ftserver;

	/* Extract the ftoptions */
	datum = SysCacheGetAttr(FOREIGNTABLEREL,
							tp,
							Anum_pg_foreign_table_ftoptions,
							&isnull);
	if (isnull)
		ft->options = NIL;
	else
		ft->options = untransformRelOptions(datum);

	ReleaseSysCache(tp);

	return ft;
}