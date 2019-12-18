#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_3__ errorMessage; } ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PQExpBufferBroken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_3__*) ; 

__attribute__((used)) static bool
saveErrorMessage(PGconn *conn, PQExpBuffer savedMessage)
{
	initPQExpBuffer(savedMessage);
	appendPQExpBufferStr(savedMessage,
						 conn->errorMessage.data);
	if (PQExpBufferBroken(savedMessage))
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
		return false;
	}
	/* Clear whatever is in errorMessage now */
	resetPQExpBuffer(&conn->errorMessage);
	return true;
}