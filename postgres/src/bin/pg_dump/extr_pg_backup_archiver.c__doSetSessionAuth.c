#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  connection; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ RestoringToDB (TYPE_2__*) ; 
 int /*<<< orphan*/  ahprintf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendStringLiteralAHX (TYPE_1__*,char const*,TYPE_2__*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  fatal (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_doSetSessionAuth(ArchiveHandle *AH, const char *user)
{
	PQExpBuffer cmd = createPQExpBuffer();

	appendPQExpBufferStr(cmd, "SET SESSION AUTHORIZATION ");

	/*
	 * SQL requires a string literal here.  Might as well be correct.
	 */
	if (user && *user)
		appendStringLiteralAHX(cmd, user, AH);
	else
		appendPQExpBufferStr(cmd, "DEFAULT");
	appendPQExpBufferChar(cmd, ';');

	if (RestoringToDB(AH))
	{
		PGresult   *res;

		res = PQexec(AH->connection, cmd->data);

		if (!res || PQresultStatus(res) != PGRES_COMMAND_OK)
			/* NOT warn_or_exit_horribly... use -O instead to skip this. */
			fatal("could not set session user to \"%s\": %s",
				  user, PQerrorMessage(AH->connection));

		PQclear(res);
	}
	else
		ahprintf(AH, "%s\n\n", cmd->data);

	destroyPQExpBuffer(cmd);
}