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
 int /*<<< orphan*/  PSQL_CMD_UNKNOWN ; 
 int do_lo_export (char*,char*) ; 
 int do_lo_import (char*,char*) ; 
 int do_lo_list () ; 
 int do_lo_unlink (char*) ; 
 int /*<<< orphan*/  expand_tilde (char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static backslashResult
exec_command_lo(PsqlScanState scan_state, bool active_branch, const char *cmd)
{
	backslashResult status = PSQL_CMD_SKIP_LINE;
	bool		success = true;

	if (active_branch)
	{
		char	   *opt1,
				   *opt2;

		opt1 = psql_scan_slash_option(scan_state,
									  OT_NORMAL, NULL, true);
		opt2 = psql_scan_slash_option(scan_state,
									  OT_NORMAL, NULL, true);

		if (strcmp(cmd + 3, "export") == 0)
		{
			if (!opt2)
			{
				pg_log_error("\\%s: missing required argument", cmd);
				success = false;
			}
			else
			{
				expand_tilde(&opt2);
				success = do_lo_export(opt1, opt2);
			}
		}

		else if (strcmp(cmd + 3, "import") == 0)
		{
			if (!opt1)
			{
				pg_log_error("\\%s: missing required argument", cmd);
				success = false;
			}
			else
			{
				expand_tilde(&opt1);
				success = do_lo_import(opt1, opt2);
			}
		}

		else if (strcmp(cmd + 3, "list") == 0)
			success = do_lo_list();

		else if (strcmp(cmd + 3, "unlink") == 0)
		{
			if (!opt1)
			{
				pg_log_error("\\%s: missing required argument", cmd);
				success = false;
			}
			else
				success = do_lo_unlink(opt1);
		}

		else
			status = PSQL_CMD_UNKNOWN;

		free(opt1);
		free(opt2);
	}
	else
		ignore_slash_options(scan_state);

	if (!success)
		status = PSQL_CMD_ERROR;

	return status;
}