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
struct TYPE_5__ {scalar_t__ sock; scalar_t__ asyncStatus; int /*<<< orphan*/  pversion; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/ * result; } ;
typedef  int /*<<< orphan*/  PQArgBlock ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_IDLE ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/ * pqFunctionCall2 (TYPE_1__*,int,int*,int*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * pqFunctionCall3 (TYPE_1__*,int,int*,int*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 

PGresult *
PQfn(PGconn *conn,
	 int fnid,
	 int *result_buf,
	 int *result_len,
	 int result_is_int,
	 const PQArgBlock *args,
	 int nargs)
{
	*result_len = 0;

	if (!conn)
		return NULL;

	/* clear the error string */
	resetPQExpBuffer(&conn->errorMessage);

	if (conn->sock == PGINVALID_SOCKET || conn->asyncStatus != PGASYNC_IDLE ||
		conn->result != NULL)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("connection in wrong state\n"));
		return NULL;
	}

	if (PG_PROTOCOL_MAJOR(conn->pversion) >= 3)
		return pqFunctionCall3(conn, fnid,
							   result_buf, result_len,
							   result_is_int,
							   args, nargs);
	else
		return pqFunctionCall2(conn, fnid,
							   result_buf, result_len,
							   result_is_int,
							   args, nargs);
}