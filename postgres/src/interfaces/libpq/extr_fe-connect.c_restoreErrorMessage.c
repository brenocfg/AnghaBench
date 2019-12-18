#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__ errorMessage; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 scalar_t__ PQExpBufferBroken (TYPE_1__*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static void
restoreErrorMessage(PGconn *conn, PQExpBuffer savedMessage)
{
	appendPQExpBufferStr(savedMessage, conn->errorMessage.data);
	resetPQExpBuffer(&conn->errorMessage);
	appendPQExpBufferStr(&conn->errorMessage, savedMessage->data);
	/* If any step above hit OOM, just report that */
	if (PQExpBufferBroken(savedMessage) ||
		PQExpBufferBroken(&conn->errorMessage))
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
	termPQExpBuffer(savedMessage);
}