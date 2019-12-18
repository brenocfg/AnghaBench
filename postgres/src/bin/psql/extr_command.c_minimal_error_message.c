#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PG_DIAG_SEVERITY ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char const*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,...) ; 

__attribute__((used)) static void
minimal_error_message(PGresult *res)
{
	PQExpBuffer msg;
	const char *fld;

	msg = createPQExpBuffer();

	fld = PQresultErrorField(res, PG_DIAG_SEVERITY);
	if (fld)
		printfPQExpBuffer(msg, "%s:  ", fld);
	else
		printfPQExpBuffer(msg, "ERROR:  ");
	fld = PQresultErrorField(res, PG_DIAG_MESSAGE_PRIMARY);
	if (fld)
		appendPQExpBufferStr(msg, fld);
	else
		appendPQExpBufferStr(msg, "(not available)");
	appendPQExpBufferChar(msg, '\n');

	pg_log_error("%s", msg->data);

	destroyPQExpBuffer(msg);
}