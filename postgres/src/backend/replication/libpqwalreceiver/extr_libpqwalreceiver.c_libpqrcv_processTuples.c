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
struct TYPE_3__ {int /*<<< orphan*/  tuplestore; int /*<<< orphan*/  tupledesc; } ;
typedef  TYPE_1__ WalRcvExecResult ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ AttrNumber ;
typedef  int /*<<< orphan*/  AttInMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int const) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int MaxTupleAttributeNumber ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfname (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessWalRcvInterrupts () ; 
 int /*<<< orphan*/ * TupleDescGetAttInMetadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int const,int) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
libpqrcv_processTuples(PGresult *pgres, WalRcvExecResult *walres,
					   const int nRetTypes, const Oid *retTypes)
{
	int			tupn;
	int			coln;
	int			nfields = PQnfields(pgres);
	HeapTuple	tuple;
	AttInMetadata *attinmeta;
	MemoryContext rowcontext;
	MemoryContext oldcontext;

	/* Make sure we got expected number of fields. */
	if (nfields != nRetTypes)
		ereport(ERROR,
				(errmsg("invalid query response"),
				 errdetail("Expected %d fields, got %d fields.",
						   nRetTypes, nfields)));

	walres->tuplestore = tuplestore_begin_heap(true, false, work_mem);

	/* Create tuple descriptor corresponding to expected result. */
	walres->tupledesc = CreateTemplateTupleDesc(nRetTypes);
	for (coln = 0; coln < nRetTypes; coln++)
		TupleDescInitEntry(walres->tupledesc, (AttrNumber) coln + 1,
						   PQfname(pgres, coln), retTypes[coln], -1, 0);
	attinmeta = TupleDescGetAttInMetadata(walres->tupledesc);

	/* No point in doing more here if there were no tuples returned. */
	if (PQntuples(pgres) == 0)
		return;

	/* Create temporary context for local allocations. */
	rowcontext = AllocSetContextCreate(CurrentMemoryContext,
									   "libpqrcv query result context",
									   ALLOCSET_DEFAULT_SIZES);

	/* Process returned rows. */
	for (tupn = 0; tupn < PQntuples(pgres); tupn++)
	{
		char	   *cstrs[MaxTupleAttributeNumber];

		ProcessWalRcvInterrupts();

		/* Do the allocations in temporary context. */
		oldcontext = MemoryContextSwitchTo(rowcontext);

		/*
		 * Fill cstrs with null-terminated strings of column values.
		 */
		for (coln = 0; coln < nfields; coln++)
		{
			if (PQgetisnull(pgres, tupn, coln))
				cstrs[coln] = NULL;
			else
				cstrs[coln] = PQgetvalue(pgres, tupn, coln);
		}

		/* Convert row to a tuple, and add it to the tuplestore */
		tuple = BuildTupleFromCStrings(attinmeta, cstrs);
		tuplestore_puttuple(walres->tuplestore, tuple);

		/* Clean up */
		MemoryContextSwitchTo(oldcontext);
		MemoryContextReset(rowcontext);
	}

	MemoryContextDelete(rowcontext);
}