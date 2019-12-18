#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ asyncStatus; int inCursor; int copy_already_done; int inStart; int /*<<< orphan*/ * inBuffer; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_COPY_BOTH ; 
 scalar_t__ PGASYNC_COPY_OUT ; 
 int getCopyDataMessage (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

int
pqGetlineAsync3(PGconn *conn, char *buffer, int bufsize)
{
	int			msgLength;
	int			avail;

	if (conn->asyncStatus != PGASYNC_COPY_OUT
		&& conn->asyncStatus != PGASYNC_COPY_BOTH)
		return -1;				/* we are not doing a copy... */

	/*
	 * Recognize the next input message.  To make life simpler for async
	 * callers, we keep returning 0 until the next message is fully available
	 * even if it is not Copy Data.  This should keep PQendcopy from blocking.
	 * (Note: unlike pqGetCopyData3, we do not change asyncStatus here.)
	 */
	msgLength = getCopyDataMessage(conn);
	if (msgLength < 0)
		return -1;				/* end-of-copy or error */
	if (msgLength == 0)
		return 0;				/* no data yet */

	/*
	 * Move data from libpq's buffer to the caller's.  In the case where a
	 * prior call found the caller's buffer too small, we use
	 * conn->copy_already_done to remember how much of the row was already
	 * returned to the caller.
	 */
	conn->inCursor += conn->copy_already_done;
	avail = msgLength - 4 - conn->copy_already_done;
	if (avail <= bufsize)
	{
		/* Able to consume the whole message */
		memcpy(buffer, &conn->inBuffer[conn->inCursor], avail);
		/* Mark message consumed */
		conn->inStart = conn->inCursor + avail;
		/* Reset state for next time */
		conn->copy_already_done = 0;
		return avail;
	}
	else
	{
		/* We must return a partial message */
		memcpy(buffer, &conn->inBuffer[conn->inCursor], bufsize);
		/* The message is NOT consumed from libpq's buffer */
		conn->copy_already_done += bufsize;
		return bufsize;
	}
}