#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_TABLE ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQdb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

bool
processQueryResult(PGconn *conn, PGresult *result)
{
	/*
	 * If it's an error, report it.  Errors about a missing table are harmless
	 * so we continue processing; but die for other errors.
	 */
	if (PQresultStatus(result) != PGRES_COMMAND_OK)
	{
		char	   *sqlState = PQresultErrorField(result, PG_DIAG_SQLSTATE);

		pg_log_error("processing of database \"%s\" failed: %s",
					 PQdb(conn), PQerrorMessage(conn));

		if (sqlState && strcmp(sqlState, ERRCODE_UNDEFINED_TABLE) != 0)
		{
			PQclear(result);
			return false;
		}
	}

	PQclear(result);
	return true;
}