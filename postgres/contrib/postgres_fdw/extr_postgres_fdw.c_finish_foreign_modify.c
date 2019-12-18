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
typedef  int /*<<< orphan*/  sql ;
struct TYPE_3__ {char* p_name; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ PgFdwModifyState ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgfdw_exec_query (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pgfdw_report_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
finish_foreign_modify(PgFdwModifyState *fmstate)
{
	Assert(fmstate != NULL);

	/* If we created a prepared statement, destroy it */
	if (fmstate->p_name)
	{
		char		sql[64];
		PGresult   *res;

		snprintf(sql, sizeof(sql), "DEALLOCATE %s", fmstate->p_name);

		/*
		 * We don't use a PG_TRY block here, so be careful not to throw error
		 * without releasing the PGresult.
		 */
		res = pgfdw_exec_query(fmstate->conn, sql);
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
			pgfdw_report_error(ERROR, res, fmstate->conn, true, sql);
		PQclear(res);
		fmstate->p_name = NULL;
	}

	/* Release remote connection */
	ReleaseConnection(fmstate->conn);
	fmstate->conn = NULL;
}