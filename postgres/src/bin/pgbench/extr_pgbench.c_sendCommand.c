#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__** commands; } ;
struct TYPE_10__ {int id; int* prepared; size_t use_file; int command; int /*<<< orphan*/  ecnt; int /*<<< orphan*/  con; } ;
struct TYPE_9__ {char** argv; scalar_t__ type; scalar_t__ argc; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ Command ;
typedef  TYPE_2__ CState ;

/* Variables and functions */
 int MAX_ARGS ; 
 int MAX_PREPARE_NAME ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQprepare (int /*<<< orphan*/ ,char*,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int PQsendQuery (int /*<<< orphan*/ ,char*) ; 
 int PQsendQueryParams (int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PQsendQueryPrepared (int /*<<< orphan*/ ,char*,scalar_t__,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ QUERY_EXTENDED ; 
 scalar_t__ QUERY_PREPARED ; 
 scalar_t__ QUERY_SIMPLE ; 
 scalar_t__ SQL_COMMAND ; 
 char* assignVariables (TYPE_2__*,char*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getQueryParams (TYPE_2__*,TYPE_1__*,char const**) ; 
 char* pg_strdup (char*) ; 
 int /*<<< orphan*/  preparedStatementName (char*,size_t,int) ; 
 scalar_t__ querymode ; 
 TYPE_3__* sql_script ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool
sendCommand(CState *st, Command *command)
{
	int			r;

	if (querymode == QUERY_SIMPLE)
	{
		char	   *sql;

		sql = pg_strdup(command->argv[0]);
		sql = assignVariables(st, sql);

		if (debug)
			fprintf(stderr, "client %d sending %s\n", st->id, sql);
		r = PQsendQuery(st->con, sql);
		free(sql);
	}
	else if (querymode == QUERY_EXTENDED)
	{
		const char *sql = command->argv[0];
		const char *params[MAX_ARGS];

		getQueryParams(st, command, params);

		if (debug)
			fprintf(stderr, "client %d sending %s\n", st->id, sql);
		r = PQsendQueryParams(st->con, sql, command->argc - 1,
							  NULL, params, NULL, NULL, 0);
	}
	else if (querymode == QUERY_PREPARED)
	{
		char		name[MAX_PREPARE_NAME];
		const char *params[MAX_ARGS];

		if (!st->prepared[st->use_file])
		{
			int			j;
			Command   **commands = sql_script[st->use_file].commands;

			for (j = 0; commands[j] != NULL; j++)
			{
				PGresult   *res;
				char		name[MAX_PREPARE_NAME];

				if (commands[j]->type != SQL_COMMAND)
					continue;
				preparedStatementName(name, st->use_file, j);
				res = PQprepare(st->con, name,
								commands[j]->argv[0], commands[j]->argc - 1, NULL);
				if (PQresultStatus(res) != PGRES_COMMAND_OK)
					fprintf(stderr, "%s", PQerrorMessage(st->con));
				PQclear(res);
			}
			st->prepared[st->use_file] = true;
		}

		getQueryParams(st, command, params);
		preparedStatementName(name, st->use_file, st->command);

		if (debug)
			fprintf(stderr, "client %d sending %s\n", st->id, name);
		r = PQsendQueryPrepared(st->con, name, command->argc - 1,
								params, NULL, NULL, 0);
	}
	else						/* unknown sql mode */
		r = 0;

	if (r == 0)
	{
		if (debug)
			fprintf(stderr, "client %d could not send %s\n",
					st->id, command->argv[0]);
		st->ecnt++;
		return false;
	}
	else
		return true;
}