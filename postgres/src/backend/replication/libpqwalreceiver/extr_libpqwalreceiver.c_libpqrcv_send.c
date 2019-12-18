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
struct TYPE_3__ {int /*<<< orphan*/  streamConn; } ;
typedef  TYPE_1__ WalReceiverConn ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 scalar_t__ PQflush (int /*<<< orphan*/ ) ; 
 scalar_t__ PQputCopyData (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pchomp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
libpqrcv_send(WalReceiverConn *conn, const char *buffer, int nbytes)
{
	if (PQputCopyData(conn->streamConn, buffer, nbytes) <= 0 ||
		PQflush(conn->streamConn))
		ereport(ERROR,
				(errmsg("could not send data to WAL stream: %s",
						pchomp(PQerrorMessage(conn->streamConn)))));
}