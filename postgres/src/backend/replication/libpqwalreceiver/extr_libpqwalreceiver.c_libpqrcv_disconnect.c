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
struct TYPE_4__ {int /*<<< orphan*/ * recvBuf; int /*<<< orphan*/  streamConn; } ;
typedef  TYPE_1__ WalReceiverConn ;

/* Variables and functions */
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfreemem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
libpqrcv_disconnect(WalReceiverConn *conn)
{
	PQfinish(conn->streamConn);
	if (conn->recvBuf != NULL)
		PQfreemem(conn->recvBuf);
	pfree(conn);
}