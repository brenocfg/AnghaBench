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
struct TYPE_2__ {int /*<<< orphan*/  vars; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  PrintVariables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 char* pg_realloc (char*,scalar_t__) ; 
 char* pg_strdup (char*) ; 
 TYPE_1__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static backslashResult
exec_command_set(PsqlScanState scan_state, bool active_branch)
{
	bool		success = true;

	if (active_branch)
	{
		char	   *opt0 = psql_scan_slash_option(scan_state,
												  OT_NORMAL, NULL, false);

		if (!opt0)
		{
			/* list all variables */
			PrintVariables(pset.vars);
			success = true;
		}
		else
		{
			/*
			 * Set variable to the concatenation of the arguments.
			 */
			char	   *newval;
			char	   *opt;

			opt = psql_scan_slash_option(scan_state,
										 OT_NORMAL, NULL, false);
			newval = pg_strdup(opt ? opt : "");
			free(opt);

			while ((opt = psql_scan_slash_option(scan_state,
												 OT_NORMAL, NULL, false)))
			{
				newval = pg_realloc(newval, strlen(newval) + strlen(opt) + 1);
				strcat(newval, opt);
				free(opt);
			}

			if (!SetVariable(pset.vars, opt0, newval))
				success = false;

			free(newval);
		}
		free(opt0);
	}
	else
		ignore_slash_options(scan_state);

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}