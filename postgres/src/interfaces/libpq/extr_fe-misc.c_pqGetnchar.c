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
struct TYPE_3__ {scalar_t__ Pfdebug; scalar_t__ inCursor; scalar_t__ inBuffer; scalar_t__ inEnd; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  fputnbytes (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 

int
pqGetnchar(char *s, size_t len, PGconn *conn)
{
	if (len > (size_t) (conn->inEnd - conn->inCursor))
		return EOF;

	memcpy(s, conn->inBuffer + conn->inCursor, len);
	/* no terminating null */

	conn->inCursor += len;

	if (conn->Pfdebug)
	{
		fprintf(conn->Pfdebug, "From backend (%lu)> ", (unsigned long) len);
		fputnbytes(conn->Pfdebug, s, len);
		fprintf(conn->Pfdebug, "\n");
	}

	return 0;
}