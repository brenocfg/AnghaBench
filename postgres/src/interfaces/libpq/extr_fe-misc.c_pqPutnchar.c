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
struct TYPE_4__ {scalar_t__ Pfdebug; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  fputnbytes (scalar_t__,char const*,size_t) ; 
 scalar_t__ pqPutMsgBytes (char const*,size_t,TYPE_1__*) ; 

int
pqPutnchar(const char *s, size_t len, PGconn *conn)
{
	if (pqPutMsgBytes(s, len, conn))
		return EOF;

	if (conn->Pfdebug)
	{
		fprintf(conn->Pfdebug, "To backend> ");
		fputnbytes(conn->Pfdebug, s, len);
		fprintf(conn->Pfdebug, "\n");
	}

	return 0;
}