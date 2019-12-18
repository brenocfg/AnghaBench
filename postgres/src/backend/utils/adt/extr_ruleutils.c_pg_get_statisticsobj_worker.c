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
struct TYPE_8__ {int dim1; int /*<<< orphan*/ * values; } ;
struct TYPE_10__ {int /*<<< orphan*/  stxrelid; TYPE_1__ stxkeys; int /*<<< orphan*/  stxname; int /*<<< orphan*/  stxnamespace; } ;
struct TYPE_9__ {char* data; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_statistic_ext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Anum_pg_statistic_ext_stxkind ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CHAROID ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATEXTOID ; 
 char STATS_EXT_DEPENDENCIES ; 
 char STATS_EXT_MCV ; 
 char STATS_EXT_NDISTINCT ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 char* generate_relation_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* get_attname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 char* quote_identifier (char*) ; 
 char* quote_qualified_identifier (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
pg_get_statisticsobj_worker(Oid statextid, bool missing_ok)
{
	Form_pg_statistic_ext statextrec;
	HeapTuple	statexttup;
	StringInfoData buf;
	int			colno;
	char	   *nsp;
	ArrayType  *arr;
	char	   *enabled;
	Datum		datum;
	bool		isnull;
	bool		ndistinct_enabled;
	bool		dependencies_enabled;
	bool		mcv_enabled;
	int			i;

	statexttup = SearchSysCache1(STATEXTOID, ObjectIdGetDatum(statextid));

	if (!HeapTupleIsValid(statexttup))
	{
		if (missing_ok)
			return NULL;
		elog(ERROR, "cache lookup failed for statistics object %u", statextid);
	}

	statextrec = (Form_pg_statistic_ext) GETSTRUCT(statexttup);

	initStringInfo(&buf);

	nsp = get_namespace_name(statextrec->stxnamespace);
	appendStringInfo(&buf, "CREATE STATISTICS %s",
					 quote_qualified_identifier(nsp,
												NameStr(statextrec->stxname)));

	/*
	 * Decode the stxkind column so that we know which stats types to print.
	 */
	datum = SysCacheGetAttr(STATEXTOID, statexttup,
							Anum_pg_statistic_ext_stxkind, &isnull);
	Assert(!isnull);
	arr = DatumGetArrayTypeP(datum);
	if (ARR_NDIM(arr) != 1 ||
		ARR_HASNULL(arr) ||
		ARR_ELEMTYPE(arr) != CHAROID)
		elog(ERROR, "stxkind is not a 1-D char array");
	enabled = (char *) ARR_DATA_PTR(arr);

	ndistinct_enabled = false;
	dependencies_enabled = false;
	mcv_enabled = false;

	for (i = 0; i < ARR_DIMS(arr)[0]; i++)
	{
		if (enabled[i] == STATS_EXT_NDISTINCT)
			ndistinct_enabled = true;
		if (enabled[i] == STATS_EXT_DEPENDENCIES)
			dependencies_enabled = true;
		if (enabled[i] == STATS_EXT_MCV)
			mcv_enabled = true;
	}

	/*
	 * If any option is disabled, then we'll need to append the types clause
	 * to show which options are enabled.  We omit the types clause on purpose
	 * when all options are enabled, so a pg_dump/pg_restore will create all
	 * statistics types on a newer postgres version, if the statistics had all
	 * options enabled on the original version.
	 */
	if (!ndistinct_enabled || !dependencies_enabled || !mcv_enabled)
	{
		bool		gotone = false;

		appendStringInfoString(&buf, " (");

		if (ndistinct_enabled)
		{
			appendStringInfoString(&buf, "ndistinct");
			gotone = true;
		}

		if (dependencies_enabled)
		{
			appendStringInfo(&buf, "%sdependencies", gotone ? ", " : "");
			gotone = true;
		}

		if (mcv_enabled)
			appendStringInfo(&buf, "%smcv", gotone ? ", " : "");

		appendStringInfoChar(&buf, ')');
	}

	appendStringInfoString(&buf, " ON ");

	for (colno = 0; colno < statextrec->stxkeys.dim1; colno++)
	{
		AttrNumber	attnum = statextrec->stxkeys.values[colno];
		char	   *attname;

		if (colno > 0)
			appendStringInfoString(&buf, ", ");

		attname = get_attname(statextrec->stxrelid, attnum, false);

		appendStringInfoString(&buf, quote_identifier(attname));
	}

	appendStringInfo(&buf, " FROM %s",
					 generate_relation_name(statextrec->stxrelid, NIL));

	ReleaseSysCache(statexttup);

	return buf.data;
}