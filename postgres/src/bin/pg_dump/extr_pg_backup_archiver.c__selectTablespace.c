#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* ropt; } ;
struct TYPE_16__ {char* currTablespace; int /*<<< orphan*/  connection; TYPE_1__ public; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
struct TYPE_14__ {scalar_t__ noTablespace; } ;
typedef  TYPE_2__ RestoreOptions ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ RestoringToDB (TYPE_4__*) ; 
 int /*<<< orphan*/  ahprintf (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  fmtId (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pg_strdup (char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  warn_or_exit_horribly (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_selectTablespace(ArchiveHandle *AH, const char *tablespace)
{
	RestoreOptions *ropt = AH->public.ropt;
	PQExpBuffer qry;
	const char *want,
			   *have;

	/* do nothing in --no-tablespaces mode */
	if (ropt->noTablespace)
		return;

	have = AH->currTablespace;
	want = tablespace;

	/* no need to do anything for non-tablespace object */
	if (!want)
		return;

	if (have && strcmp(want, have) == 0)
		return;					/* no need to do anything */

	qry = createPQExpBuffer();

	if (strcmp(want, "") == 0)
	{
		/* We want the tablespace to be the database's default */
		appendPQExpBufferStr(qry, "SET default_tablespace = ''");
	}
	else
	{
		/* We want an explicit tablespace */
		appendPQExpBuffer(qry, "SET default_tablespace = %s", fmtId(want));
	}

	if (RestoringToDB(AH))
	{
		PGresult   *res;

		res = PQexec(AH->connection, qry->data);

		if (!res || PQresultStatus(res) != PGRES_COMMAND_OK)
			warn_or_exit_horribly(AH,
								  "could not set default_tablespace to %s: %s",
								  fmtId(want), PQerrorMessage(AH->connection));

		PQclear(res);
	}
	else
		ahprintf(AH, "%s;\n\n", qry->data);

	if (AH->currTablespace)
		free(AH->currTablespace);
	AH->currTablespace = pg_strdup(want);

	destroyPQExpBuffer(qry);
}