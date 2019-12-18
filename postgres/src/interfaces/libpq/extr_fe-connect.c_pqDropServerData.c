#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ pgParameterStatus ;
struct TYPE_7__ {int std_strings; char* last_sqlstate; int auth_req_received; int password_needed; int write_failed; scalar_t__ be_key; scalar_t__ be_pid; TYPE_1__* write_err_msg; TYPE_1__* lobjfuncs; scalar_t__ sversion; int /*<<< orphan*/  client_encoding; TYPE_1__* pstatus; int /*<<< orphan*/ * notifyTail; TYPE_1__* notifyHead; } ;
typedef  TYPE_1__ PGnotify ;
typedef  TYPE_3__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PG_SQL_ASCII ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
pqDropServerData(PGconn *conn)
{
	PGnotify   *notify;
	pgParameterStatus *pstatus;

	/* Forget pending notifies */
	notify = conn->notifyHead;
	while (notify != NULL)
	{
		PGnotify   *prev = notify;

		notify = notify->next;
		free(prev);
	}
	conn->notifyHead = conn->notifyTail = NULL;

	/* Reset ParameterStatus data, as well as variables deduced from it */
	pstatus = conn->pstatus;
	while (pstatus != NULL)
	{
		pgParameterStatus *prev = pstatus;

		pstatus = pstatus->next;
		free(prev);
	}
	conn->pstatus = NULL;
	conn->client_encoding = PG_SQL_ASCII;
	conn->std_strings = false;
	conn->sversion = 0;

	/* Drop large-object lookup data */
	if (conn->lobjfuncs)
		free(conn->lobjfuncs);
	conn->lobjfuncs = NULL;

	/* Reset assorted other per-connection state */
	conn->last_sqlstate[0] = '\0';
	conn->auth_req_received = false;
	conn->password_needed = false;
	conn->write_failed = false;
	if (conn->write_err_msg)
		free(conn->write_err_msg);
	conn->write_err_msg = NULL;
	conn->be_pid = 0;
	conn->be_key = 0;
}