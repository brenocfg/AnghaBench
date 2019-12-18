#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ status; int /*<<< orphan*/  errorMessage; } ;
struct TYPE_9__ {scalar_t__ resultStatus; int /*<<< orphan*/  errMsg; } ;
typedef  TYPE_1__ PGresult ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ PGRES_COPY_BOTH ; 
 scalar_t__ PGRES_COPY_IN ; 
 scalar_t__ PGRES_COPY_OUT ; 
 scalar_t__ PGRES_FATAL_ERROR ; 
 int /*<<< orphan*/  PQclear (TYPE_1__*) ; 
 TYPE_1__* PQgetResult (TYPE_2__*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqCatenateResultError (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PGresult *
PQexecFinish(PGconn *conn)
{
	PGresult   *result;
	PGresult   *lastResult;

	/*
	 * For backwards compatibility, return the last result if there are more
	 * than one --- but merge error messages if we get more than one error
	 * result.
	 *
	 * We have to stop if we see copy in/out/both, however. We will resume
	 * parsing after application performs the data transfer.
	 *
	 * Also stop if the connection is lost (else we'll loop infinitely).
	 */
	lastResult = NULL;
	while ((result = PQgetResult(conn)) != NULL)
	{
		if (lastResult)
		{
			if (lastResult->resultStatus == PGRES_FATAL_ERROR &&
				result->resultStatus == PGRES_FATAL_ERROR)
			{
				pqCatenateResultError(lastResult, result->errMsg);
				PQclear(result);
				result = lastResult;

				/*
				 * Make sure PQerrorMessage agrees with concatenated result
				 */
				resetPQExpBuffer(&conn->errorMessage);
				appendPQExpBufferStr(&conn->errorMessage, result->errMsg);
			}
			else
				PQclear(lastResult);
		}
		lastResult = result;
		if (result->resultStatus == PGRES_COPY_IN ||
			result->resultStatus == PGRES_COPY_OUT ||
			result->resultStatus == PGRES_COPY_BOTH ||
			conn->status == CONNECTION_BAD)
			break;
	}

	return lastResult;
}