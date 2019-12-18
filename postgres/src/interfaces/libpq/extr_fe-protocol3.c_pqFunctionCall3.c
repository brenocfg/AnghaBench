#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int inCursor; int inStart; int inEnd; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  result; } ;
struct TYPE_25__ {int integer; scalar_t__ ptr; } ;
struct TYPE_26__ {int len; TYPE_1__ u; scalar_t__ isint; } ;
typedef  TYPE_2__ PQArgBlock ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ PGconn ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  ExecStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PGRES_FATAL_ERROR ; 
 int /*<<< orphan*/ * PQmakeEmptyPGresult (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_LONG_MESSAGE_TYPE (char) ; 
 int /*<<< orphan*/  getNotify (TYPE_3__*) ; 
 int /*<<< orphan*/  getParameterStatus (TYPE_3__*) ; 
 int /*<<< orphan*/  getReadyForQuery (TYPE_3__*) ; 
 int /*<<< orphan*/  handleSyncLoss (TYPE_3__*,char,int) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqCheckInBufferSpace (int,TYPE_3__*) ; 
 scalar_t__ pqFlush (TYPE_3__*) ; 
 int /*<<< orphan*/  pqGetErrorNotice3 (TYPE_3__*,int) ; 
 scalar_t__ pqGetInt (int*,int,TYPE_3__*) ; 
 scalar_t__ pqGetc (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  pqGetnchar (char*,int,TYPE_3__*) ; 
 int /*<<< orphan*/ * pqPrepareAsyncResult (TYPE_3__*) ; 
 scalar_t__ pqPutInt (int,int,TYPE_3__*) ; 
 scalar_t__ pqPutMsgEnd (TYPE_3__*) ; 
 scalar_t__ pqPutMsgStart (float,int,TYPE_3__*) ; 
 scalar_t__ pqPutnchar (char*,int,TYPE_3__*) ; 
 scalar_t__ pqReadData (TYPE_3__*) ; 
 int /*<<< orphan*/  pqSaveErrorResult (TYPE_3__*) ; 
 scalar_t__ pqWait (int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 

PGresult *
pqFunctionCall3(PGconn *conn, Oid fnid,
				int *result_buf, int *actual_result_len,
				int result_is_int,
				const PQArgBlock *args, int nargs)
{
	bool		needInput = false;
	ExecStatusType status = PGRES_FATAL_ERROR;
	char		id;
	int			msgLength;
	int			avail;
	int			i;

	/* PQfn already validated connection state */

	if (pqPutMsgStart('F', false, conn) < 0 ||	/* function call msg */
		pqPutInt(fnid, 4, conn) < 0 ||	/* function id */
		pqPutInt(1, 2, conn) < 0 || /* # of format codes */
		pqPutInt(1, 2, conn) < 0 || /* format code: BINARY */
		pqPutInt(nargs, 2, conn) < 0)	/* # of args */
	{
		/* error message should be set up already */
		return NULL;
	}

	for (i = 0; i < nargs; ++i)
	{							/* len.int4 + contents	   */
		if (pqPutInt(args[i].len, 4, conn))
			return NULL;
		if (args[i].len == -1)
			continue;			/* it's NULL */

		if (args[i].isint)
		{
			if (pqPutInt(args[i].u.integer, args[i].len, conn))
				return NULL;
		}
		else
		{
			if (pqPutnchar((char *) args[i].u.ptr, args[i].len, conn))
				return NULL;
		}
	}

	if (pqPutInt(1, 2, conn) < 0)	/* result format code: BINARY */
		return NULL;

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
		needInput = true;

		conn->inCursor = conn->inStart;
		if (pqGetc(&id, conn))
			continue;
		if (pqGetInt(&msgLength, 4, conn))
			continue;

		/*
		 * Try to validate message type/length here.  A length less than 4 is
		 * definitely broken.  Large lengths should only be believed for a few
		 * message types.
		 */
		if (msgLength < 4)
		{
			handleSyncLoss(conn, id, msgLength);
			break;
		}
		if (msgLength > 30000 && !VALID_LONG_MESSAGE_TYPE(id))
		{
			handleSyncLoss(conn, id, msgLength);
			break;
		}

		/*
		 * Can't process if message body isn't all here yet.
		 */
		msgLength -= 4;
		avail = conn->inEnd - conn->inCursor;
		if (avail < msgLength)
		{
			/*
			 * Before looping, enlarge the input buffer if needed to hold the
			 * whole message.  See notes in parseInput.
			 */
			if (pqCheckInBufferSpace(conn->inCursor + (size_t) msgLength,
									 conn))
			{
				/*
				 * XXX add some better recovery code... plan is to skip over
				 * the message using its length, then report an error. For the
				 * moment, just treat this like loss of sync (which indeed it
				 * might be!)
				 */
				handleSyncLoss(conn, id, msgLength);
				break;
			}
			continue;
		}

		/*
		 * We should see V or E response to the command, but might get N
		 * and/or A notices first. We also need to swallow the final Z before
		 * returning.
		 */
		switch (id)
		{
			case 'V':			/* function result */
				if (pqGetInt(actual_result_len, 4, conn))
					continue;
				if (*actual_result_len != -1)
				{
					if (result_is_int)
					{
						if (pqGetInt(result_buf, *actual_result_len, conn))
							continue;
					}
					else
					{
						if (pqGetnchar((char *) result_buf,
									   *actual_result_len,
									   conn))
							continue;
					}
				}
				/* correctly finished function result message */
				status = PGRES_COMMAND_OK;
				break;
			case 'E':			/* error return */
				if (pqGetErrorNotice3(conn, true))
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
				if (pqGetErrorNotice3(conn, false))
					continue;
				break;
			case 'Z':			/* backend is ready for new query */
				if (getReadyForQuery(conn))
					continue;
				/* consume the message and exit */
				conn->inStart += 5 + msgLength;
				/* if we saved a result object (probably an error), use it */
				if (conn->result)
					return pqPrepareAsyncResult(conn);
				return PQmakeEmptyPGresult(conn, status);
			case 'S':			/* parameter status */
				if (getParameterStatus(conn))
					continue;
				break;
			default:
				/* The backend violates the protocol. */
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("protocol error: id=0x%x\n"),
								  id);
				pqSaveErrorResult(conn);
				/* trust the specified message length as what to skip */
				conn->inStart += 5 + msgLength;
				return pqPrepareAsyncResult(conn);
		}
		/* Completed this message, keep going */
		/* trust the specified message length as what to skip */
		conn->inStart += 5 + msgLength;
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