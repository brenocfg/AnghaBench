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
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  asyncStatus; int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_BAD ; 
 int /*<<< orphan*/  PGASYNC_READY ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  pqDropConnection (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pqSaveErrorResult (TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char,int) ; 

__attribute__((used)) static void
handleSyncLoss(PGconn *conn, char id, int msgLength)
{
	printfPQExpBuffer(&conn->errorMessage,
					  libpq_gettext(
									"lost synchronization with server: got message type \"%c\", length %d\n"),
					  id, msgLength);
	/* build an error result holding the error message */
	pqSaveErrorResult(conn);
	conn->asyncStatus = PGASYNC_READY;	/* drop out of GetResult wait loop */
	/* flush input data since we're giving up on processing it */
	pqDropConnection(conn, true);
	conn->status = CONNECTION_BAD;	/* No more connection to backend */
}