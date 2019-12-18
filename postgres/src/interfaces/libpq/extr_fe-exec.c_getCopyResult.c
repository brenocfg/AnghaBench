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
struct TYPE_8__ {scalar_t__ status; TYPE_1__* result; int /*<<< orphan*/  asyncStatus; } ;
struct TYPE_7__ {scalar_t__ resultStatus; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_2__ PGconn ;
typedef  scalar_t__ ExecStatusType ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  PGASYNC_IDLE ; 
 int /*<<< orphan*/ * PQmakeEmptyPGresult (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * pqPrepareAsyncResult (TYPE_2__*) ; 
 int /*<<< orphan*/  pqSaveErrorResult (TYPE_2__*) ; 

__attribute__((used)) static PGresult *
getCopyResult(PGconn *conn, ExecStatusType copytype)
{
	/*
	 * If the server connection has been lost, don't pretend everything is
	 * hunky-dory; instead return a PGRES_FATAL_ERROR result, and reset the
	 * asyncStatus to idle (corresponding to what we'd do if we'd detected I/O
	 * error in the earlier steps in PQgetResult).  The text returned in the
	 * result is whatever is in conn->errorMessage; we hope that was filled
	 * with something relevant when the lost connection was detected.
	 */
	if (conn->status != CONNECTION_OK)
	{
		pqSaveErrorResult(conn);
		conn->asyncStatus = PGASYNC_IDLE;
		return pqPrepareAsyncResult(conn);
	}

	/* If we have an async result for the COPY, return that */
	if (conn->result && conn->result->resultStatus == copytype)
		return pqPrepareAsyncResult(conn);

	/* Otherwise, invent a suitable PGresult */
	return PQmakeEmptyPGresult(conn, copytype);
}