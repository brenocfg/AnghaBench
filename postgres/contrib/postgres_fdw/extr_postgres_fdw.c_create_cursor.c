#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_11__ {TYPE_6__* ps_ExprContext; } ;
struct TYPE_12__ {TYPE_1__ ps; } ;
struct TYPE_15__ {TYPE_2__ ss; scalar_t__ fdw_state; } ;
struct TYPE_14__ {int numParams; char** param_values; int cursor_exists; int eof_reached; scalar_t__ fetch_ct_2; scalar_t__ next_tuple; scalar_t__ num_tuples; int /*<<< orphan*/ * tuples; int /*<<< orphan*/  query; int /*<<< orphan*/  cursor_number; int /*<<< orphan*/  param_exprs; int /*<<< orphan*/  param_flinfo; int /*<<< orphan*/ * conn; } ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ StringInfoData ;
typedef  TYPE_4__ PgFdwScanState ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_5__ ForeignScanState ;
typedef  TYPE_6__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQsendQueryParams (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgfdw_get_result (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgfdw_report_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_query_params (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static void
create_cursor(ForeignScanState *node)
{
	PgFdwScanState *fsstate = (PgFdwScanState *) node->fdw_state;
	ExprContext *econtext = node->ss.ps.ps_ExprContext;
	int			numParams = fsstate->numParams;
	const char **values = fsstate->param_values;
	PGconn	   *conn = fsstate->conn;
	StringInfoData buf;
	PGresult   *res;

	/*
	 * Construct array of query parameter values in text format.  We do the
	 * conversions in the short-lived per-tuple context, so as not to cause a
	 * memory leak over repeated scans.
	 */
	if (numParams > 0)
	{
		MemoryContext oldcontext;

		oldcontext = MemoryContextSwitchTo(econtext->ecxt_per_tuple_memory);

		process_query_params(econtext,
							 fsstate->param_flinfo,
							 fsstate->param_exprs,
							 values);

		MemoryContextSwitchTo(oldcontext);
	}

	/* Construct the DECLARE CURSOR command */
	initStringInfo(&buf);
	appendStringInfo(&buf, "DECLARE c%u CURSOR FOR\n%s",
					 fsstate->cursor_number, fsstate->query);

	/*
	 * Notice that we pass NULL for paramTypes, thus forcing the remote server
	 * to infer types for all parameters.  Since we explicitly cast every
	 * parameter (see deparse.c), the "inference" is trivial and will produce
	 * the desired result.  This allows us to avoid assuming that the remote
	 * server has the same OIDs we do for the parameters' types.
	 */
	if (!PQsendQueryParams(conn, buf.data, numParams,
						   NULL, values, NULL, NULL, 0))
		pgfdw_report_error(ERROR, NULL, conn, false, buf.data);

	/*
	 * Get the result, and check for success.
	 *
	 * We don't use a PG_TRY block here, so be careful not to throw error
	 * without releasing the PGresult.
	 */
	res = pgfdw_get_result(conn, buf.data);
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
		pgfdw_report_error(ERROR, res, conn, true, fsstate->query);
	PQclear(res);

	/* Mark the cursor as created, and show no tuples have been retrieved */
	fsstate->cursor_exists = true;
	fsstate->tuples = NULL;
	fsstate->num_tuples = 0;
	fsstate->next_tuple = 0;
	fsstate->fetch_ct_2 = 0;
	fsstate->eof_reached = false;

	/* Clean up */
	pfree(buf.data);
}