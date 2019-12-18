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
struct TYPE_11__ {char* currTableAm; int /*<<< orphan*/  connection; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
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
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  fmtId (char const*) ; 
 char* pg_strdup (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  warn_or_exit_horribly (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_selectTableAccessMethod(ArchiveHandle *AH, const char *tableam)
{
	PQExpBuffer cmd;
	const char *want,
			   *have;

	have = AH->currTableAm;
	want = tableam;

	if (!want)
		return;

	if (have && strcmp(want, have) == 0)
		return;

	cmd = createPQExpBuffer();
	appendPQExpBuffer(cmd, "SET default_table_access_method = %s;", fmtId(want));

	if (RestoringToDB(AH))
	{
		PGresult   *res;

		res = PQexec(AH->connection, cmd->data);

		if (!res || PQresultStatus(res) != PGRES_COMMAND_OK)
			warn_or_exit_horribly(AH,
								  "could not set default_table_access_method: %s",
								  PQerrorMessage(AH->connection));

		PQclear(res);
	}
	else
		ahprintf(AH, "%s\n\n", cmd->data);

	destroyPQExpBuffer(cmd);

	AH->currTableAm = pg_strdup(want);
}