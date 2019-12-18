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
struct TYPE_3__ {int outBufSize; char* outBuffer; int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,char*) ; 
 char* realloc (char*,int) ; 

int
pqCheckOutBufferSpace(size_t bytes_needed, PGconn *conn)
{
	int			newsize = conn->outBufSize;
	char	   *newbuf;

	/* Quick exit if we have enough space */
	if (bytes_needed <= (size_t) newsize)
		return 0;

	/*
	 * If we need to enlarge the buffer, we first try to double it in size; if
	 * that doesn't work, enlarge in multiples of 8K.  This avoids thrashing
	 * the malloc pool by repeated small enlargements.
	 *
	 * Note: tests for newsize > 0 are to catch integer overflow.
	 */
	do
	{
		newsize *= 2;
	} while (newsize > 0 && bytes_needed > (size_t) newsize);

	if (newsize > 0 && bytes_needed <= (size_t) newsize)
	{
		newbuf = realloc(conn->outBuffer, newsize);
		if (newbuf)
		{
			/* realloc succeeded */
			conn->outBuffer = newbuf;
			conn->outBufSize = newsize;
			return 0;
		}
	}

	newsize = conn->outBufSize;
	do
	{
		newsize += 8192;
	} while (newsize > 0 && bytes_needed > (size_t) newsize);

	if (newsize > 0 && bytes_needed <= (size_t) newsize)
	{
		newbuf = realloc(conn->outBuffer, newsize);
		if (newbuf)
		{
			/* realloc succeeded */
			conn->outBuffer = newbuf;
			conn->outBufSize = newsize;
			return 0;
		}
	}

	/* realloc failed. Probably out of memory */
	printfPQExpBuffer(&conn->errorMessage,
					  "cannot allocate memory for output buffer\n");
	return EOF;
}