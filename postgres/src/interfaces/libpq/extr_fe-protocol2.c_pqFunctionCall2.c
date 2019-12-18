#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  inCursor; int /*<<< orphan*/  inStart; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  result; } ;
struct TYPE_22__ {int integer; scalar_t__ ptr; } ;
struct TYPE_23__ {int len; TYPE_1__ u; scalar_t__ isint; } ;
typedef  TYPE_2__ PQArgBlock ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ PGconn ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  ExecStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PGRES_FATAL_ERROR ; 
 int /*<<< orphan*/ * PQmakeEmptyPGresult (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getNotify (TYPE_3__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqFlush (TYPE_3__*) ; 
 int /*<<< orphan*/  pqGetErrorNotice2 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pqGetInt (int*,int,TYPE_3__*) ; 
 scalar_t__ pqGetc (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  pqGetnchar (char*,int,TYPE_3__*) ; 
 int /*<<< orphan*/ * pqPrepareAsyncResult (TYPE_3__*) ; 
 scalar_t__ pqPutInt (int,int,TYPE_3__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_3__*) ; 
 scalar_t__ pqPutMsgStart (float,int,TYPE_3__*) ; 
 scalar_t__ pqPutnchar (char*,int,TYPE_3__*) ; 
 scalar_t__ pqPuts (char*,TYPE_3__*) ; 
 scalar_t__ pqReadData (TYPE_3__*) ; 
 int /*<<< orphan*/  pqSaveErrorResult (TYPE_3__*) ; 
 scalar_t__ pqWait (int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 

PGresult *
pqFunctionCall2(PGconn *conn, Oid fnid,
				int *result_buf, int *actual_result_len,
				int result_is_int,
				const PQArgBlock *args, int nargs)
{
	bool		needInput = false;
	ExecStatusType status = PGRES_FATAL_ERROR;
	char		id;
	int			i;

	/* PQfn already validated connection state */

	if (pqPutMsgStart('F', false, conn) < 0 ||	/* function call msg */
		pqPuts(" ", conn) < 0 ||	/* dummy string */
		pqPutInt(fnid, 4, conn) != 0 || /* function id */
		pqPutInt(nargs, 4, conn) != 0)	/* # of args */
	{
		/* error message should be set up already */
		return NULL;
	}

	for (i = 0; i < nargs; ++i)
	{							/* len.int4 + contents	   */
		if (pqPutInt(args[i].len, 4, conn))
			return NULL;

		if (args[i].isint)
		{
			if (pqPutInt(args[i].u.integer, 4, conn))
				return NULL;
		}
		else
		{
			if (pqPutnchar((char *) args[i].u.ptr, args[i].len, conn))
				return NULL;
		}
	}

	if (pqPutMsgEnd(conn) < 0 ||
		pqFlush(conn))
		return NULL;

	for (;;)
	{
		if (needInput)
		{
			/* Wait for some data to arrive (or for the channel to close) */
			if (pqWait(true, false, conn) ||
				pqReadData(conn) < 0)
				break;
		}

		/*
		 * Scan the message. If we run out of data, loop around to try again.
		 */
		conn->inCursor = conn->inStart;
		needInput = true;

		if (pqGetc(&id, conn))
			continue;

		/*
		 * We should see V or E response to the command, but might get N
		 * and/or A notices first. We also need to swallow the final Z before
		 * returning.
		 */
		switch (id)
		{
			case 'V':			/* function result */
				if (pqGetc(&id, conn))
					continue;
				if (id == 'G')
				{
					/* function returned nonempty value */
					if (pqGetInt(actual_result_len, 4, conn))
						continue;
					if (result_is_int)
					{
						if (pqGetInt(result_buf, 4, conn))
							continue;
					}
					else
					{
						if (pqGetnchar((char *) result_buf,
									   *actual_result_len,
									   conn))
							continue;
					}
					if (pqGetc(&id, conn))	/* get the last '0' */
						continue;
				}
				if (id == '0')
				{
					/* correctly finished function result message */
					status = PGRES_COMMAND_OK;
				}
				else
				{
					/* The backend violates the protocol. */
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext("protocol error: id=0x%x\n"),
									  id);
					pqSaveErrorResult(conn);
					conn->inStart = conn->inCursor;
					return pqPrepareAsyncResult(conn);
				}
				break;
			case 'E':			/* error return */
				if (pqGetErrorNotice2(conn, true))
					continue;
				status = PGRES_FATAL_ERROR;
				break;
			case 'A':			/* notify message */
				/* handle notify and go back to processing return values */
				if (getNotify(conn))
					continue;
				break;
			case 'N':			/* notice */
				/* handle notice and go back to processing return values */
				if (pqGetErrorNotice2(conn, false))
					continue;
				break;
			case 'Z':			/* backend is ready for new query */
				/* consume the message and exit */
				conn->inStart = conn->inCursor;
				/* if we saved a result object (probably an error), use it */
				if (conn->result)
					return pqPrepareAsyncResult(conn);
				return PQmakeEmptyPGresult(conn, status);
			default:
				/* The backend violates the protocol. */
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("protocol error: id=0x%x\n"),
								  id);
				pqSaveErrorResult(conn);
				conn->inStart = conn->inCursor;
				return pqPrepareAsyncResult(conn);
		}
		/* Completed this message, keep going */
		conn->inStart = conn->inCursor;
		needInput = false;
	}

	/*
	 * We fall out of the loop only upon failing to read data.
	 * conn->errorMessage has been set by pqWait or pqReadData. We want to
	 * append it to any already-received error message.
	 */
	pqSaveErrorResult(conn);
	return pqPrepareAsyncResult(conn);
}