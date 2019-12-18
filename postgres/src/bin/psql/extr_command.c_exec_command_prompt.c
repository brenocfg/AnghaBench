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
typedef  int /*<<< orphan*/  backslashResult ;
struct TYPE_2__ {int /*<<< orphan*/  vars; int /*<<< orphan*/  inputfile; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* gets_fromFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 scalar_t__ pg_malloc (int) ; 
 TYPE_1__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static backslashResult
exec_command_prompt(PsqlScanState scan_state, bool active_branch,
					const char *cmd)
{
	bool		success = true;

	if (active_branch)
	{
		char	   *opt,
				   *prompt_text = NULL;
		char	   *arg1,
				   *arg2;

		arg1 = psql_scan_slash_option(scan_state, OT_NORMAL, NULL, false);
		arg2 = psql_scan_slash_option(scan_state, OT_NORMAL, NULL, false);

		if (!arg1)
		{
			pg_log_error("\\%s: missing required argument", cmd);
			success = false;
		}
		else
		{
			char	   *result;

			if (arg2)
			{
				prompt_text = arg1;
				opt = arg2;
			}
			else
				opt = arg1;

			if (!pset.inputfile)
			{
				result = (char *) pg_malloc(4096);
				simple_prompt(prompt_text, result, 4096, true);
			}
			else
			{
				if (prompt_text)
				{
					fputs(prompt_text, stdout);
					fflush(stdout);
				}
				result = gets_fromFile(stdin);
				if (!result)
				{
					pg_log_error("\\%s: could not read value for variable",
								 cmd);
					success = false;
				}
			}

			if (result &&
				!SetVariable(pset.vars, opt, result))
				success = false;

			if (result)
				free(result);
			if (prompt_text)
				free(prompt_text);
			free(opt);
		}
	}
	else
		ignore_slash_options(scan_state);

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}