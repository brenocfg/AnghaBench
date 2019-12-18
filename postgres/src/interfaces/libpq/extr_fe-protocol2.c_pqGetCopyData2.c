#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ inCursor; scalar_t__ inStart; scalar_t__ inEnd; char* inBuffer; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  asyncStatus; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PGASYNC_BUSY ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ pqReadData (TYPE_1__*) ; 
 scalar_t__ pqWait (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
pqGetCopyData2(PGconn *conn, char **buffer, int async)
{
	bool		found;
	int			msgLength;

	for (;;)
	{
		/*
		 * Do we have a complete line of data?
		 */
		conn->inCursor = conn->inStart;
		found = false;
		while (conn->inCursor < conn->inEnd)
		{
			char		c = conn->inBuffer[conn->inCursor++];

			if (c == '\n')
			{
				found = true;
				break;
			}
		}
		if (!found)
			goto nodata;
		msgLength = conn->inCursor - conn->inStart;

		/*
		 * If it's the end-of-data marker, consume it, exit COPY_OUT mode, and
		 * let caller read status with PQgetResult().
		 */
		if (msgLength == 3 &&
			strncmp(&conn->inBuffer[conn->inStart], "\\.\n", 3) == 0)
		{
			conn->inStart = conn->inCursor;
			conn->asyncStatus = PGASYNC_BUSY;
			return -1;
		}

		/*
		 * Pass the line back to the caller.
		 */
		*buffer = (char *) malloc(msgLength + 1);
		if (*buffer == NULL)
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("out of memory\n"));
			return -2;
		}
		memcpy(*buffer, &conn->inBuffer[conn->inStart], msgLength);
		(*buffer)[msgLength] = '\0';	/* Add terminating null */

		/* Mark message consumed */
		conn->inStart = conn->inCursor;

		return msgLength;

nodata:
		/* Don't block if async read requested */
		if (async)
			return 0;
		/* Need to load more data */
		if (pqWait(true, false, conn) ||
			pqReadData(conn) < 0)
			return -2;
	}
}