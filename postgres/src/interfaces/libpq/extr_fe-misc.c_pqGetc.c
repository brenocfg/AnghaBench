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
struct TYPE_3__ {scalar_t__ inCursor; scalar_t__ inEnd; char* inBuffer; scalar_t__ Pfdebug; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char) ; 

int
pqGetc(char *result, PGconn *conn)
{
	if (conn->inCursor >= conn->inEnd)
		return EOF;

	*result = conn->inBuffer[conn->inCursor++];

	if (conn->Pfdebug)
		fprintf(conn->Pfdebug, "From backend> %c\n", *result);

	return 0;
}