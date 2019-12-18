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
struct TYPE_5__ {scalar_t__ sock; scalar_t__ asyncStatus; scalar_t__ inStart; scalar_t__ inEnd; char* inBuffer; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ PGASYNC_COPY_OUT ; 
 scalar_t__ PGINVALID_SOCKET ; 
 scalar_t__ pqReadData (TYPE_1__*) ; 
 scalar_t__ pqWait (int,int,TYPE_1__*) ; 

int
pqGetline2(PGconn *conn, char *s, int maxlen)
{
	int			result = 1;		/* return value if buffer overflows */

	if (conn->sock == PGINVALID_SOCKET ||
		conn->asyncStatus != PGASYNC_COPY_OUT)
	{
		*s = '\0';
		return EOF;
	}

	/*
	 * Since this is a purely synchronous routine, we don't bother to maintain
	 * conn->inCursor; there is no need to back up.
	 */
	while (maxlen > 1)
	{
		if (conn->inStart < conn->inEnd)
		{
			char		c = conn->inBuffer[conn->inStart++];

			if (c == '\n')
			{
				result = 0;		/* success exit */
				break;
			}
			*s++ = c;
			maxlen--;
		}
		else
		{
			/* need to load more data */
			if (pqWait(true, false, conn) ||
				pqReadData(conn) < 0)
			{
				result = EOF;
				break;
			}
		}
	}
	*s = '\0';

	return result;
}