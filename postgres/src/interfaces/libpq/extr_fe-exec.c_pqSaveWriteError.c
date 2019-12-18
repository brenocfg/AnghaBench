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
struct TYPE_4__ {char* write_err_msg; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 char* libpq_gettext (char*) ; 
 int /*<<< orphan*/  pqCatenateResultError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pqSaveErrorResult (TYPE_1__*) ; 

__attribute__((used)) static void
pqSaveWriteError(PGconn *conn)
{
	/*
	 * Ensure conn->result is an error result, and add anything in
	 * conn->errorMessage to it.
	 */
	pqSaveErrorResult(conn);

	/*
	 * Now append write_err_msg to that.  If it's null because of previous
	 * strdup failure, do what we can.  (It's likely our machinations here are
	 * all getting OOM failures as well, but ...)
	 */
	if (conn->write_err_msg && conn->write_err_msg[0] != '\0')
		pqCatenateResultError(conn->result, conn->write_err_msg);
	else
		pqCatenateResultError(conn->result,
							  libpq_gettext("write to server failed\n"));
}