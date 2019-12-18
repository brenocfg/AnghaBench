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
typedef  int /*<<< orphan*/  prep_name ;
struct TYPE_3__ {char* p_name; int /*<<< orphan*/  query; int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ PgFdwModifyState ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int GetPrepStmtNumber (int /*<<< orphan*/ ) ; 
 int NAMEDATALEN ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQsendPrepare (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgfdw_get_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgfdw_report_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
prepare_foreign_modify(PgFdwModifyState *fmstate)
{
	char		prep_name[NAMEDATALEN];
	char	   *p_name;
	PGresult   *res;

	/* Construct name we'll use for the prepared statement. */
	snprintf(prep_name, sizeof(prep_name), "pgsql_fdw_prep_%u",
			 GetPrepStmtNumber(fmstate->conn));
	p_name = pstrdup(prep_name);

	/*
	 * We intentionally do not specify parameter types here, but leave the
	 * remote server to derive them by default.  This avoids possible problems
	 * with the remote server using different type OIDs than we do.  All of
	 * the prepared statements we use in this module are simple enough that
	 * the remote server will make the right choices.
	 */
	if (!PQsendPrepare(fmstate->conn,
					   p_name,
					   fmstate->query,
					   0,
					   NULL))
		pgfdw_report_error(ERROR, NULL, fmstate->conn, false, fmstate->query);

	/*
	 * Get the result, and check for success.
	 *
	 * We don't use a PG_TRY block here, so be careful not to throw error
	 * without releasing the PGresult.
	 */
	res = pgfdw_get_result(fmstate->conn, fmstate->query);
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
		pgfdw_report_error(ERROR, res, fmstate->conn, true, fmstate->query);
	PQclear(res);

	/* This action shows that the prepare has been done. */
	fmstate->p_name = p_name;
}