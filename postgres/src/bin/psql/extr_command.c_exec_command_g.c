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
struct TYPE_2__ {int g_expanded; int /*<<< orphan*/ * gfname; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_FILEPIPE ; 
 int /*<<< orphan*/  PSQL_CMD_SEND ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  expand_tilde (char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_filepipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pg_strdup (char*) ; 
 TYPE_1__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static backslashResult
exec_command_g(PsqlScanState scan_state, bool active_branch, const char *cmd)
{
	backslashResult status = PSQL_CMD_SKIP_LINE;

	if (active_branch)
	{
		char	   *fname = psql_scan_slash_option(scan_state,
												   OT_FILEPIPE, NULL, false);

		if (!fname)
			pset.gfname = NULL;
		else
		{
			expand_tilde(&fname);
			pset.gfname = pg_strdup(fname);
		}
		free(fname);
		if (strcmp(cmd, "gx") == 0)
			pset.g_expanded = true;
		status = PSQL_CMD_SEND;
	}
	else
		ignore_slash_filepipe(scan_state);

	return status;
}