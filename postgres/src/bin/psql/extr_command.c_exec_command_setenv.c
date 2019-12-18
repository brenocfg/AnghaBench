#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  backslashResult ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 char* psprintf (char*,char*,char*) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static backslashResult
exec_command_setenv(PsqlScanState scan_state, bool active_branch,
					const char *cmd)
{
	bool		success = true;

	if (active_branch)
	{
		char	   *envvar = psql_scan_slash_option(scan_state,
													OT_NORMAL, NULL, false);
		char	   *envval = psql_scan_slash_option(scan_state,
													OT_NORMAL, NULL, false);

		if (!envvar)
		{
			pg_log_error("\\%s: missing required argument", cmd);
			success = false;
		}
		else if (strchr(envvar, '=') != NULL)
		{
			pg_log_error("\\%s: environment variable name must not contain \"=\"",
						 cmd);
			success = false;
		}
		else if (!envval)
		{
			/* No argument - unset the environment variable */
			unsetenv(envvar);
			success = true;
		}
		else
		{
			/* Set variable to the value of the next argument */
			char	   *newval;

			newval = psprintf("%s=%s", envvar, envval);
			putenv(newval);
			success = true;

			/*
			 * Do not free newval here, it will screw up the environment if
			 * you do. See putenv man page for details. That means we leak a
			 * bit of memory here, but not enough to worry about.
			 */
		}
		free(envvar);
		free(envval);
	}
	else
		ignore_slash_options(scan_state);

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}