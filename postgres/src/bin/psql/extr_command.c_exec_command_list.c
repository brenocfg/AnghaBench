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
 int listAllDbs (char*,int) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static backslashResult
exec_command_list(PsqlScanState scan_state, bool active_branch, const char *cmd)
{
	bool		success = true;

	if (active_branch)
	{
		char	   *pattern;
		bool		show_verbose;

		pattern = psql_scan_slash_option(scan_state,
										 OT_NORMAL, NULL, true);

		show_verbose = strchr(cmd, '+') ? true : false;

		success = listAllDbs(pattern, show_verbose);

		if (pattern)
			free(pattern);
	}
	else
		ignore_slash_options(scan_state);

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}