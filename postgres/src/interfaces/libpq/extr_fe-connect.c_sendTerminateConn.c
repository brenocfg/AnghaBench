#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sock; scalar_t__ status; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  pqFlush (TYPE_1__*) ; 
 int /*<<< orphan*/  pqPutMsgEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  pqPutMsgStart (char,int,TYPE_1__*) ; 

__attribute__((used)) static void
sendTerminateConn(PGconn *conn)
{
	/*
	 * Note that the protocol doesn't allow us to send Terminate messages
	 * during the startup phase.
	 */
	if (conn->sock != PGINVALID_SOCKET && conn->status == CONNECTION_OK)
	{
		/*
		 * Try to send "close connection" message to backend. Ignore any
		 * error.
		 */
		pqPutMsgStart('X', false, conn);
		pqPutMsgEnd(conn);
		(void) pqFlush(conn);
	}
}