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
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char const* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_nicely (int) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 int /*<<< orphan*/  pg_log_info (char*,char const*) ; 

__attribute__((used)) static void
executeCommand(PGconn *conn, const char *query)
{
	PGresult   *res;

	pg_log_info("executing %s", query);

	res = PQexec(conn, query);
	if (!res ||
		PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		pg_log_error("query failed: %s", PQerrorMessage(conn));
		pg_log_error("query was: %s", query);
		PQfinish(conn);
		exit_nicely(1);
	}

	PQclear(res);
}