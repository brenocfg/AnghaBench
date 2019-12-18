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
struct TYPE_5__ {scalar_t__ asyncStatus; int /*<<< orphan*/  pversion; int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_COPY_BOTH ; 
 scalar_t__ PGASYNC_COPY_OUT ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int pqGetCopyData2 (TYPE_1__*,char**,int) ; 
 int pqGetCopyData3 (TYPE_1__*,char**,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
PQgetCopyData(PGconn *conn, char **buffer, int async)
{
	*buffer = NULL;				/* for all failure cases */
	if (!conn)
		return -2;
	if (conn->asyncStatus != PGASYNC_COPY_OUT &&
		conn->asyncStatus != PGASYNC_COPY_BOTH)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("no COPY in progress\n"));
		return -2;
	}
	if (PG_PROTOCOL_MAJOR(conn->pversion) >= 3)
		return pqGetCopyData3(conn, buffer, async);
	else
		return pqGetCopyData2(conn, buffer, async);
}