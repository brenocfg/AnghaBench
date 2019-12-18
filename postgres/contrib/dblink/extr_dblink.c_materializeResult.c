#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_16__ {scalar_t__ resultinfo; } ;
struct TYPE_15__ {scalar_t__ returnMode; TYPE_2__* setDesc; int /*<<< orphan*/ * setResult; TYPE_1__* econtext; } ;
struct TYPE_14__ {int natts; } ;
struct TYPE_13__ {int /*<<< orphan*/  ecxt_per_query_memory; } ;
typedef  TYPE_3__ ReturnSetInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  AttrNumber ;
typedef  int /*<<< orphan*/  AttInMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ *,char**) ; 
 TYPE_2__* CreateTemplateTupleDesc (int) ; 
 TYPE_2__* CreateTupleDescCopy (TYPE_2__*) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQcmdStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ SFRM_Materialize ; 
 int /*<<< orphan*/  TEXTOID ; 
#define  TYPEFUNC_COMPOSITE 129 
#define  TYPEFUNC_RECORD 128 
 int /*<<< orphan*/ * TupleDescGetAttInMetadata (TYPE_2__*) ; 
 int /*<<< orphan*/  TupleDescInitEntry (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int applyRemoteGucs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int get_call_result_type (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__**) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  restoreLocalGucs (int) ; 
 int /*<<< orphan*/ * tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_donestoring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
materializeResult(FunctionCallInfo fcinfo, PGconn *conn, PGresult *res)
{
	ReturnSetInfo *rsinfo = (ReturnSetInfo *) fcinfo->resultinfo;

	/* prepTuplestoreResult must have been called previously */
	Assert(rsinfo->returnMode == SFRM_Materialize);

	PG_TRY();
	{
		TupleDesc	tupdesc;
		bool		is_sql_cmd;
		int			ntuples;
		int			nfields;

		if (PQresultStatus(res) == PGRES_COMMAND_OK)
		{
			is_sql_cmd = true;

			/*
			 * need a tuple descriptor representing one TEXT column to return
			 * the command status string as our result tuple
			 */
			tupdesc = CreateTemplateTupleDesc(1);
			TupleDescInitEntry(tupdesc, (AttrNumber) 1, "status",
							   TEXTOID, -1, 0);
			ntuples = 1;
			nfields = 1;
		}
		else
		{
			Assert(PQresultStatus(res) == PGRES_TUPLES_OK);

			is_sql_cmd = false;

			/* get a tuple descriptor for our result type */
			switch (get_call_result_type(fcinfo, NULL, &tupdesc))
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
			ntuples = PQntuples(res);
			nfields = PQnfields(res);
		}

		/*
		 * check result and tuple descriptor have the same number of columns
		 */
		if (nfields != tupdesc->natts)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("remote query result rowtype does not match "
							"the specified FROM clause rowtype")));

		if (ntuples > 0)
		{
			AttInMetadata *attinmeta;
			int			nestlevel = -1;
			Tuplestorestate *tupstore;
			MemoryContext oldcontext;
			int			row;
			char	  **values;

			attinmeta = TupleDescGetAttInMetadata(tupdesc);

			/* Set GUCs to ensure we read GUC-sensitive data types correctly */
			if (!is_sql_cmd)
				nestlevel = applyRemoteGucs(conn);

			oldcontext = MemoryContextSwitchTo(
											   rsinfo->econtext->ecxt_per_query_memory);
			tupstore = tuplestore_begin_heap(true, false, work_mem);
			rsinfo->setResult = tupstore;
			rsinfo->setDesc = tupdesc;
			MemoryContextSwitchTo(oldcontext);

			values = (char **) palloc(nfields * sizeof(char *));

			/* put all tuples into the tuplestore */
			for (row = 0; row < ntuples; row++)
			{
				HeapTuple	tuple;

				if (!is_sql_cmd)
				{
					int			i;

					for (i = 0; i < nfields; i++)
					{
						if (PQgetisnull(res, row, i))
							values[i] = NULL;
						else
							values[i] = PQgetvalue(res, row, i);
					}
				}
				else
				{
					values[0] = PQcmdStatus(res);
				}

				/* build the tuple and put it into the tuplestore. */
				tuple = BuildTupleFromCStrings(attinmeta, values);
				tuplestore_puttuple(tupstore, tuple);
			}

			/* clean up GUC settings, if we changed any */
			restoreLocalGucs(nestlevel);

			/* clean up and return the tuplestore */
			tuplestore_donestoring(tupstore);
		}
	}
	PG_FINALLY();
	{
		/* be sure to release the libpq result */
		PQclear(res);
	}
	PG_END_TRY();
}