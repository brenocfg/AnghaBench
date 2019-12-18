#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  promptStatus_t ;
struct TYPE_9__ {scalar_t__ meta; scalar_t__ type; int argc; char** argv; int /*<<< orphan*/ * varprefix; int /*<<< orphan*/ * first_line; } ;
struct TYPE_8__ {char const* desc; int weight; TYPE_2__** commands; int /*<<< orphan*/  stats; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  scalar_t__ PsqlScanResult ;
typedef  TYPE_1__ ParsedScript ;
typedef  int /*<<< orphan*/  PQExpBufferData ;
typedef  TYPE_2__ Command ;

/* Variables and functions */
 int COMMANDS_ALLOC_NUM ; 
 scalar_t__ META_GSET ; 
 scalar_t__ PSCAN_BACKSLASH ; 
 scalar_t__ PSCAN_EOL ; 
 scalar_t__ PSCAN_INCOMPLETE ; 
 scalar_t__ SQL_COMMAND ; 
 int /*<<< orphan*/  addScript (TYPE_1__) ; 
 TYPE_2__* create_sql_command (int /*<<< orphan*/ *,char const*) ; 
 int expr_scanner_get_lineno (int /*<<< orphan*/ ,int) ; 
 int expr_scanner_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_command (TYPE_2__*) ; 
 int /*<<< orphan*/  initPQExpBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ pg_realloc (TYPE_2__**,int) ; 
 void* pg_strdup (char*) ; 
 int /*<<< orphan*/  pgbench_callbacks ; 
 TYPE_2__* process_backslash_command (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ psql_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psql_scan_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psql_scan_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psql_scan_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psql_scan_setup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  syntax_error (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  termPQExpBuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ParseScript(const char *script, const char *desc, int weight)
{
	ParsedScript ps;
	PsqlScanState sstate;
	PQExpBufferData line_buf;
	int			alloc_num;
	int			index;
	int			lineno;
	int			start_offset;

#define COMMANDS_ALLOC_NUM 128
	alloc_num = COMMANDS_ALLOC_NUM;

	/* Initialize all fields of ps */
	ps.desc = desc;
	ps.weight = weight;
	ps.commands = (Command **) pg_malloc(sizeof(Command *) * alloc_num);
	initStats(&ps.stats, 0);

	/* Prepare to parse script */
	sstate = psql_scan_create(&pgbench_callbacks);

	/*
	 * Ideally, we'd scan scripts using the encoding and stdstrings settings
	 * we get from a DB connection.  However, without major rearrangement of
	 * pgbench's argument parsing, we can't have a DB connection at the time
	 * we parse scripts.  Using SQL_ASCII (encoding 0) should work well enough
	 * with any backend-safe encoding, though conceivably we could be fooled
	 * if a script file uses a client-only encoding.  We also assume that
	 * stdstrings should be true, which is a bit riskier.
	 */
	psql_scan_setup(sstate, script, strlen(script), 0, true);
	start_offset = expr_scanner_offset(sstate) - 1;

	initPQExpBuffer(&line_buf);

	index = 0;

	for (;;)
	{
		PsqlScanResult sr;
		promptStatus_t prompt;
		Command    *command = NULL;

		resetPQExpBuffer(&line_buf);
		lineno = expr_scanner_get_lineno(sstate, start_offset);

		sr = psql_scan(sstate, &line_buf, &prompt);

		/* If we collected a new SQL command, process that */
		command = create_sql_command(&line_buf, desc);

		/* store new command */
		if (command)
			ps.commands[index++] = command;

		/* If we reached a backslash, process that */
		if (sr == PSCAN_BACKSLASH)
		{
			command = process_backslash_command(sstate, desc);

			if (command)
			{
				/*
				 * If this is gset, merge into the preceding command. (We
				 * don't use a command slot in this case).
				 */
				if (command->meta == META_GSET)
				{
					Command    *cmd;

					if (index == 0)
						syntax_error(desc, lineno, NULL, NULL,
									 "\\gset must follow a SQL command",
									 NULL, -1);

					cmd = ps.commands[index - 1];

					if (cmd->type != SQL_COMMAND ||
						cmd->varprefix != NULL)
						syntax_error(desc, lineno, NULL, NULL,
									 "\\gset must follow a SQL command",
									 cmd->first_line, -1);

					/* get variable prefix */
					if (command->argc <= 1 || command->argv[1][0] == '\0')
						cmd->varprefix = pg_strdup("");
					else
						cmd->varprefix = pg_strdup(command->argv[1]);

					/* cleanup unused command */
					free_command(command);

					continue;
				}

				/* Attach any other backslash command as a new command */
				ps.commands[index++] = command;
			}
		}

		/*
		 * Since we used a command slot, allocate more if needed.  Note we
		 * always allocate one more in order to accommodate the NULL
		 * terminator below.
		 */
		if (index >= alloc_num)
		{
			alloc_num += COMMANDS_ALLOC_NUM;
			ps.commands = (Command **)
				pg_realloc(ps.commands, sizeof(Command *) * alloc_num);
		}

		/* Done if we reached EOF */
		if (sr == PSCAN_INCOMPLETE || sr == PSCAN_EOL)
			break;
	}

	ps.commands[index] = NULL;

	addScript(ps);

	termPQExpBuffer(&line_buf);
	psql_scan_finish(sstate);
	psql_scan_destroy(sstate);
}