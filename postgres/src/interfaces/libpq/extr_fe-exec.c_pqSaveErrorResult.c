#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ resultStatus; int /*<<< orphan*/ * errMsg; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__ errorMessage; TYPE_5__* result; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 scalar_t__ PGRES_FATAL_ERROR ; 
 TYPE_5__* PQmakeEmptyPGresult (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  pqCatenateResultError (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqClearAsyncResult (TYPE_2__*) ; 

void
pqSaveErrorResult(PGconn *conn)
{
	/*
	 * If no old async result, just let PQmakeEmptyPGresult make one. Likewise
	 * if old result is not an error message.
	 */
	if (conn->result == NULL ||
		conn->result->resultStatus != PGRES_FATAL_ERROR ||
		conn->result->errMsg == NULL)
	{
		pqClearAsyncResult(conn);
		conn->result = PQmakeEmptyPGresult(conn, PGRES_FATAL_ERROR);
	}
	else
	{
		/* Else, concatenate error message to existing async result. */
		pqCatenateResultError(conn->result, conn->errorMessage.data);
	}
}