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

/* Variables and functions */
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
run_simple_query(const char *sql)
{
	PGresult   *res;
	char	   *result;

	res = PQexec(conn, sql);

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
		pg_fatal("error running query (%s) in source server: %s",
				 sql, PQresultErrorMessage(res));

	/* sanity check the result set */
	if (PQnfields(res) != 1 || PQntuples(res) != 1 || PQgetisnull(res, 0, 0))
		pg_fatal("unexpected result set from query");

	result = pg_strdup(PQgetvalue(res, 0, 0));

	PQclear(res);

	return result;
}