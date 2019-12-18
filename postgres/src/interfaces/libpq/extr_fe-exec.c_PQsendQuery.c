#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  asyncStatus; scalar_t__ last_query; int /*<<< orphan*/  queryclass; int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PGASYNC_BUSY ; 
 int /*<<< orphan*/  PGQUERY_SIMPLE ; 
 int /*<<< orphan*/  PQsendQueryStart (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqFlush (TYPE_1__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_1__*) ; 
 scalar_t__ pqPutMsgStart (char,int,TYPE_1__*) ; 
 scalar_t__ pqPuts (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strdup (char const*) ; 

int
PQsendQuery(PGconn *conn, const char *query)
{
	if (!PQsendQueryStart(conn))
		return 0;

	/* check the argument */
	if (!query)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("command string is a null pointer\n"));
		return 0;
	}

	/* construct the outgoing Query message */
	if (pqPutMsgStart('Q', false, conn) < 0 ||
		pqPuts(query, conn) < 0 ||
		pqPutMsgEnd(conn) < 0)
	{
		/* error message should be set up already */
		return 0;
	}

	/* remember we are using simple query protocol */
	conn->queryclass = PGQUERY_SIMPLE;

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
	{
		/* error message should be set up already */
		return 0;
	}

	/* OK, it's launched! */
	conn->asyncStatus = PGASYNC_BUSY;
	return 1;
}