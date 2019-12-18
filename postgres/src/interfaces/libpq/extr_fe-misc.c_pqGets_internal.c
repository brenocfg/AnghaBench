#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* inBuffer; int inCursor; int inEnd; scalar_t__ Pfdebug; } ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  appendBinaryPQExpBuffer (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static int
pqGets_internal(PQExpBuffer buf, PGconn *conn, bool resetbuffer)
{
	/* Copy conn data to locals for faster search loop */
	char	   *inBuffer = conn->inBuffer;
	int			inCursor = conn->inCursor;
	int			inEnd = conn->inEnd;
	int			slen;

	while (inCursor < inEnd && inBuffer[inCursor])
		inCursor++;

	if (inCursor >= inEnd)
		return EOF;

	slen = inCursor - conn->inCursor;

	if (resetbuffer)
		resetPQExpBuffer(buf);

	appendBinaryPQExpBuffer(buf, inBuffer + conn->inCursor, slen);

	conn->inCursor = ++inCursor;

	if (conn->Pfdebug)
		fprintf(conn->Pfdebug, "From backend> \"%s\"\n",
				buf->data);

	return 0;
}