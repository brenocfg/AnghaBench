#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ backslashResult ;
struct TYPE_2__ {int /*<<< orphan*/  queryFout; scalar_t__ cur_cmd_interactive; } ;
typedef  int /*<<< orphan*/ * PsqlScanState ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  int /*<<< orphan*/ * ConditionalStack ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFSTATE_IGNORED ; 
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  OT_WHOLE_LINE ; 
 scalar_t__ PSQL_CMD_ERROR ; 
 scalar_t__ PSQL_CMD_UNKNOWN ; 
 int conditional_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conditional_stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conditional_stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 int /*<<< orphan*/  pg_log_info (char*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,char*,char*) ; 
 TYPE_1__ pset ; 
 char* psql_scan_slash_command (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psql_scan_slash_command_end (int /*<<< orphan*/ *) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

backslashResult
HandleSlashCmds(PsqlScanState scan_state,
				ConditionalStack cstack,
				PQExpBuffer query_buf,
				PQExpBuffer previous_buf)
{
	backslashResult status;
	char	   *cmd;
	char	   *arg;

	Assert(scan_state != NULL);
	Assert(cstack != NULL);

	/* Parse off the command name */
	cmd = psql_scan_slash_command(scan_state);

	/* And try to execute it */
	status = exec_command(cmd, scan_state, cstack, query_buf, previous_buf);

	if (status == PSQL_CMD_UNKNOWN)
	{
		pg_log_error("invalid command \\%s", cmd);
		if (pset.cur_cmd_interactive)
			pg_log_info("Try \\? for help.");
		status = PSQL_CMD_ERROR;
	}

	if (status != PSQL_CMD_ERROR)
	{
		/*
		 * Eat any remaining arguments after a valid command.  We want to
		 * suppress evaluation of backticks in this situation, so transiently
		 * push an inactive conditional-stack entry.
		 */
		bool		active_branch = conditional_active(cstack);

		conditional_stack_push(cstack, IFSTATE_IGNORED);
		while ((arg = psql_scan_slash_option(scan_state,
											 OT_NORMAL, NULL, false)))
		{
			if (active_branch)
				pg_log_warning("\\%s: extra argument \"%s\" ignored", cmd, arg);
			free(arg);
		}
		conditional_stack_pop(cstack);
	}
	else
	{
		/* silently throw away rest of line after an erroneous command */
		while ((arg = psql_scan_slash_option(scan_state,
											 OT_WHOLE_LINE, NULL, false)))
			free(arg);
	}

	/* if there is a trailing \\, swallow it */
	psql_scan_slash_command_end(scan_state);

	free(cmd);

	/* some commands write to queryFout, so make sure output is sent */
	fflush(pset.queryFout);

	return status;
}