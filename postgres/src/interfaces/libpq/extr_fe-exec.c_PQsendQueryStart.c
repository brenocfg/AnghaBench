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
struct TYPE_4__ {scalar_t__ status; scalar_t__ asyncStatus; int singleRowMode; int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ PGASYNC_IDLE ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  pqClearAsyncResult (TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
PQsendQueryStart(PGconn *conn)
{
	if (!conn)
		return false;

	/* clear the error string */
	resetPQExpBuffer(&conn->errorMessage);

	/* Don't try to send if we know there's no live connection. */
	if (conn->status != CONNECTION_OK)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("no connection to the server\n"));
		return false;
	}
	/* Can't send while already busy, either. */
	if (conn->asyncStatus != PGASYNC_IDLE)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("another command is already in progress\n"));
		return false;
	}

	/* initialize async result-accumulation state */
	pqClearAsyncResult(conn);

	/* reset single-row processing mode */
	conn->singleRowMode = false;

	/* ready to send command message */
	return true;
}