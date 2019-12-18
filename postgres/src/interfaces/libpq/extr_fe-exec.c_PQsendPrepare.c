#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  asyncStatus; scalar_t__ last_query; int /*<<< orphan*/  queryclass; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  pversion; } ;
typedef  TYPE_1__ PGconn ;
typedef  int Oid ;

/* Variables and functions */
 int /*<<< orphan*/  PGASYNC_BUSY ; 
 int /*<<< orphan*/  PGQUERY_PREPARE ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQsendQueryStart (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqFlush (TYPE_1__*) ; 
 scalar_t__ pqPutInt (int const,int,TYPE_1__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_1__*) ; 
 scalar_t__ pqPutMsgStart (char,int,TYPE_1__*) ; 
 scalar_t__ pqPuts (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strdup (char const*) ; 

int
PQsendPrepare(PGconn *conn,
			  const char *stmtName, const char *query,
			  int nParams, const Oid *paramTypes)
{
	if (!PQsendQueryStart(conn))
		return 0;

	/* check the arguments */
	if (!stmtName)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("statement name is a null pointer\n"));
		return 0;
	}
	if (!query)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("command string is a null pointer\n"));
		return 0;
	}
	if (nParams < 0 || nParams > 65535)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("number of parameters must be between 0 and 65535\n"));
		return 0;
	}

	/* This isn't gonna work on a 2.0 server */
	if (PG_PROTOCOL_MAJOR(conn->pversion) < 3)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("function requires at least protocol version 3.0\n"));
		return 0;
	}

	/* construct the Parse message */
	if (pqPutMsgStart('P', false, conn) < 0 ||
		pqPuts(stmtName, conn) < 0 ||
		pqPuts(query, conn) < 0)
		goto sendFailed;

	if (nParams > 0 && paramTypes)
	{
		int			i;

		if (pqPutInt(nParams, 2, conn) < 0)
			goto sendFailed;
		for (i = 0; i < nParams; i++)
		{
			if (pqPutInt(paramTypes[i], 4, conn) < 0)
				goto sendFailed;
		}
	}
	else
	{
		if (pqPutInt(0, 2, conn) < 0)
			goto sendFailed;
	}
	if (pqPutMsgEnd(conn) < 0)
		goto sendFailed;

	/* construct the Sync message */
	if (pqPutMsgStart('S', false, conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
		goto sendFailed;

	/* remember we are doing just a Parse */
	conn->queryclass = PGQUERY_PREPARE;

	/* and remember the query text too, if possible */
	/* if insufficient memory, last_query just winds up NULL */
	if (conn->last_query)
		free(conn->last_query);
	conn->last_query = strdup(query);

	/*
	 * Give the data a push.  In nonblock mode, don't complain if we're unable
	 * to send it all; PQgetResult() will do any additional flushing needed.
	 */
	if (pqFlush(conn) < 0)
		goto sendFailed;

	/* OK, it's launched! */
	conn->asyncStatus = PGASYNC_BUSY;
	return 1;

sendFailed:
	/* error message should be set up already */
	return 0;
}