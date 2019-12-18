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
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ PGRES_COPY_BOTH ; 
 scalar_t__ PGRES_COPY_IN ; 
 scalar_t__ PGRES_COPY_OUT ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQsendQuery (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libpqrcv_PQgetResult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PGresult *
libpqrcv_PQexec(PGconn *streamConn, const char *query)
{
	PGresult   *lastResult = NULL;

	/*
	 * PQexec() silently discards any prior query results on the connection.
	 * This is not required for this function as it's expected that the caller
	 * (which is this library in all cases) will behave correctly and we don't
	 * have to be backwards compatible with old libpq.
	 */

	/*
	 * Submit the query.  Since we don't use non-blocking mode, this could
	 * theoretically block.  In practice, since we don't send very long query
	 * strings, the risk seems negligible.
	 */
	if (!PQsendQuery(streamConn, query))
		return NULL;

	for (;;)
	{
		/* Wait for, and collect, the next PGresult. */
		PGresult   *result;

		result = libpqrcv_PQgetResult(streamConn);
		if (result == NULL)
			break;				/* query is complete, or failure */

		/*
		 * Emulate PQexec()'s behavior of returning the last result when there
		 * are many.  We are fine with returning just last error message.
		 */
		PQclear(lastResult);
		lastResult = result;

		if (PQresultStatus(lastResult) == PGRES_COPY_IN ||
			PQresultStatus(lastResult) == PGRES_COPY_OUT ||
			PQresultStatus(lastResult) == PGRES_COPY_BOTH ||
			PQstatus(streamConn) == CONNECTION_BAD)
			break;
	}

	return lastResult;
}