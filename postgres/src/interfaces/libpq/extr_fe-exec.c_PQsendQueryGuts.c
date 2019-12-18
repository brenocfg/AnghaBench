#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  asyncStatus; int /*<<< orphan*/ * last_query; int /*<<< orphan*/  queryclass; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  pversion; } ;
typedef  TYPE_1__ PGconn ;
typedef  int Oid ;

/* Variables and functions */
 int /*<<< orphan*/  PGASYNC_BUSY ; 
 int /*<<< orphan*/  PGQUERY_EXTENDED ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqFlush (TYPE_1__*) ; 
 scalar_t__ pqPutInt (int const,int,TYPE_1__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_1__*) ; 
 scalar_t__ pqPutMsgStart (char,int,TYPE_1__*) ; 
 scalar_t__ pqPutc (char,TYPE_1__*) ; 
 scalar_t__ pqPutnchar (char const* const,int,TYPE_1__*) ; 
 scalar_t__ pqPuts (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int strlen (char const* const) ; 

__attribute__((used)) static int
PQsendQueryGuts(PGconn *conn,
				const char *command,
				const char *stmtName,
				int nParams,
				const Oid *paramTypes,
				const char *const *paramValues,
				const int *paramLengths,
				const int *paramFormats,
				int resultFormat)
{
	int			i;

	/* This isn't gonna work on a 2.0 server */
	if (PG_PROTOCOL_MAJOR(conn->pversion) < 3)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("function requires at least protocol version 3.0\n"));
		return 0;
	}

	/*
	 * We will send Parse (if needed), Bind, Describe Portal, Execute, Sync,
	 * using specified statement name and the unnamed portal.
	 */

	if (command)
	{
		/* construct the Parse message */
		if (pqPutMsgStart('P', false, conn) < 0 ||
			pqPuts(stmtName, conn) < 0 ||
			pqPuts(command, conn) < 0)
			goto sendFailed;
		if (nParams > 0 && paramTypes)
		{
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
	}

	/* Construct the Bind message */
	if (pqPutMsgStart('B', false, conn) < 0 ||
		pqPuts("", conn) < 0 ||
		pqPuts(stmtName, conn) < 0)
		goto sendFailed;

	/* Send parameter formats */
	if (nParams > 0 && paramFormats)
	{
		if (pqPutInt(nParams, 2, conn) < 0)
			goto sendFailed;
		for (i = 0; i < nParams; i++)
		{
			if (pqPutInt(paramFormats[i], 2, conn) < 0)
				goto sendFailed;
		}
	}
	else
	{
		if (pqPutInt(0, 2, conn) < 0)
			goto sendFailed;
	}

	if (pqPutInt(nParams, 2, conn) < 0)
		goto sendFailed;

	/* Send parameters */
	for (i = 0; i < nParams; i++)
	{
		if (paramValues && paramValues[i])
		{
			int			nbytes;

			if (paramFormats && paramFormats[i] != 0)
			{
				/* binary parameter */
				if (paramLengths)
					nbytes = paramLengths[i];
				else
				{
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext("length must be given for binary parameter\n"));
					goto sendFailed;
				}
			}
			else
			{
				/* text parameter, do not use paramLengths */
				nbytes = strlen(paramValues[i]);
			}
			if (pqPutInt(nbytes, 4, conn) < 0 ||
				pqPutnchar(paramValues[i], nbytes, conn) < 0)
				goto sendFailed;
		}
		else
		{
			/* take the param as NULL */
			if (pqPutInt(-1, 4, conn) < 0)
				goto sendFailed;
		}
	}
	if (pqPutInt(1, 2, conn) < 0 ||
		pqPutInt(resultFormat, 2, conn))
		goto sendFailed;
	if (pqPutMsgEnd(conn) < 0)
		goto sendFailed;

	/* construct the Describe Portal message */
	if (pqPutMsgStart('D', false, conn) < 0 ||
		pqPutc('P', conn) < 0 ||
		pqPuts("", conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
		goto sendFailed;

	/* construct the Execute message */
	if (pqPutMsgStart('E', false, conn) < 0 ||
		pqPuts("", conn) < 0 ||
		pqPutInt(0, 4, conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
		goto sendFailed;

	/* construct the Sync message */
	if (pqPutMsgStart('S', false, conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
		goto sendFailed;

	/* remember we are using extended query protocol */
	conn->queryclass = PGQUERY_EXTENDED;

	/* and remember the query text too, if possible */
	/* if insufficient memory, last_query just winds up NULL */
	if (conn->last_query)
		free(conn->last_query);
	if (command)
		conn->last_query = strdup(command);
	else
		conn->last_query = NULL;

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