#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char** cstrs; int /*<<< orphan*/  tmpcontext; int /*<<< orphan*/ * tuplestore; int /*<<< orphan*/  attinmeta; TYPE_6__* fcinfo; } ;
typedef  TYPE_2__ storeInfo ;
typedef  TYPE_3__* TupleDesc ;
struct TYPE_15__ {scalar_t__ resultinfo; } ;
struct TYPE_14__ {TYPE_3__* setDesc; int /*<<< orphan*/ * setResult; TYPE_1__* econtext; } ;
struct TYPE_13__ {int natts; } ;
struct TYPE_11__ {int /*<<< orphan*/  ecxt_per_query_memory; } ;
typedef  TYPE_4__ ReturnSetInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ ,char**) ; 
 TYPE_3__* CreateTupleDescCopy (TYPE_3__*) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
#define  TYPEFUNC_COMPOSITE 129 
#define  TYPEFUNC_RECORD 128 
 int /*<<< orphan*/  TupleDescGetAttInMetadata (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int get_call_result_type (TYPE_6__*,int /*<<< orphan*/ *,TYPE_3__**) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char**) ; 
 int /*<<< orphan*/ * tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
storeRow(volatile storeInfo *sinfo, PGresult *res, bool first)
{
	int			nfields = PQnfields(res);
	HeapTuple	tuple;
	int			i;
	MemoryContext oldcontext;

	if (first)
	{
		/* Prepare for new result set */
		ReturnSetInfo *rsinfo = (ReturnSetInfo *) sinfo->fcinfo->resultinfo;
		TupleDesc	tupdesc;

		/*
		 * It's possible to get more than one result set if the query string
		 * contained multiple SQL commands.  In that case, we follow PQexec's
		 * traditional behavior of throwing away all but the last result.
		 */
		if (sinfo->tuplestore)
			tuplestore_end(sinfo->tuplestore);
		sinfo->tuplestore = NULL;

		/* get a tuple descriptor for our result type */
		switch (get_call_result_type(sinfo->fcinfo, NULL, &tupdesc))
		{
			case TYPEFUNC_COMPOSITE:
				/* success */
				break;
			case TYPEFUNC_RECORD:
				/* failed to determine actual type of RECORD */
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("function returning record called in context "
								"that cannot accept type record")));
				break;
			default:
				/* result type isn't composite */
				elog(ERROR, "return type must be a row type");
				break;
		}

		/* make sure we have a persistent copy of the tupdesc */
		tupdesc = CreateTupleDescCopy(tupdesc);

		/* check result and tuple descriptor have the same number of columns */
		if (nfields != tupdesc->natts)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("remote query result rowtype does not match "
							"the specified FROM clause rowtype")));

		/* Prepare attinmeta for later data conversions */
		sinfo->attinmeta = TupleDescGetAttInMetadata(tupdesc);

		/* Create a new, empty tuplestore */
		oldcontext = MemoryContextSwitchTo(rsinfo->econtext->ecxt_per_query_memory);
		sinfo->tuplestore = tuplestore_begin_heap(true, false, work_mem);
		rsinfo->setResult = sinfo->tuplestore;
		rsinfo->setDesc = tupdesc;
		MemoryContextSwitchTo(oldcontext);

		/* Done if empty resultset */
		if (PQntuples(res) == 0)
			return;

		/*
		 * Set up sufficiently-wide string pointers array; this won't change
		 * in size so it's easy to preallocate.
		 */
		if (sinfo->cstrs)
			pfree(sinfo->cstrs);
		sinfo->cstrs = (char **) palloc(nfields * sizeof(char *));
	}

	/* Should have a single-row result if we get here */
	Assert(PQntuples(res) == 1);

	/*
	 * Do the following work in a temp context that we reset after each tuple.
	 * This cleans up not only the data we have direct access to, but any
	 * cruft the I/O functions might leak.
	 */
	oldcontext = MemoryContextSwitchTo(sinfo->tmpcontext);

	/*
	 * Fill cstrs with null-terminated strings of column values.
	 */
	for (i = 0; i < nfields; i++)
	{
		if (PQgetisnull(res, 0, i))
			sinfo->cstrs[i] = NULL;
		else
			sinfo->cstrs[i] = PQgetvalue(res, 0, i);
	}

	/* Convert row to a tuple, and add it to the tuplestore */
	tuple = BuildTupleFromCStrings(sinfo->attinmeta, sinfo->cstrs);

	tuplestore_puttuple(sinfo->tuplestore, tuple);

	/* Clean up */
	MemoryContextSwitchTo(oldcontext);
	MemoryContextReset(sinfo->tmpcontext);
}