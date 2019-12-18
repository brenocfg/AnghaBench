#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ asyncStatus; scalar_t__ inCursor; scalar_t__ inStart; scalar_t__ inEnd; char* inBuffer; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_COPY_OUT ; 

int
pqGetlineAsync2(PGconn *conn, char *buffer, int bufsize)
{
	int			avail;

	if (conn->asyncStatus != PGASYNC_COPY_OUT)
		return -1;				/* we are not doing a copy... */

	/*
	 * Move data from libpq's buffer to the caller's. We want to accept data
	 * only in units of whole lines, not partial lines.  This ensures that we
	 * can recognize the terminator line "\\.\n".  (Otherwise, if it happened
	 * to cross a packet/buffer boundary, we might hand the first one or two
	 * characters off to the caller, which we shouldn't.)
	 */

	conn->inCursor = conn->inStart;

	avail = bufsize;
	while (avail > 0 && conn->inCursor < conn->inEnd)
	{
		char		c = conn->inBuffer[conn->inCursor++];

		*buffer++ = c;
		--avail;
		if (c == '\n')
		{
			/* Got a complete line; mark the data removed from libpq */
			conn->inStart = conn->inCursor;
			/* Is it the endmarker line? */
			if (bufsize - avail == 3 && buffer[-3] == '\\' && buffer[-2] == '.')
				return -1;
			/* No, return the data line to the caller */
			return bufsize - avail;
		}
	}

	/*
	 * We don't have a complete line. We'd prefer to leave it in libpq's
	 * buffer until the rest arrives, but there is a special case: what if the
	 * line is longer than the buffer the caller is offering us?  In that case
	 * we'd better hand over a partial line, else we'd get into an infinite
	 * loop. Do this in a way that ensures we can't misrecognize a terminator
	 * line later: leave last 3 characters in libpq buffer.
	 */
	if (avail == 0 && bufsize > 3)
	{
		conn->inStart = conn->inCursor - 3;
		return bufsize - 3;
	}
	return 0;
}