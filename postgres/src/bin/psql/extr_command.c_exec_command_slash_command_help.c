#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  backslashResult ;
struct TYPE_4__ {int /*<<< orphan*/  pager; } ;
struct TYPE_5__ {TYPE_1__ topt; } ;
struct TYPE_6__ {TYPE_2__ popt; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  helpVariables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 TYPE_3__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slashUsage (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static backslashResult
exec_command_slash_command_help(PsqlScanState scan_state, bool active_branch)
{
	if (active_branch)
	{
		char	   *opt0 = psql_scan_slash_option(scan_state,
												  OT_NORMAL, NULL, false);

		if (!opt0 || strcmp(opt0, "commands") == 0)
			slashUsage(pset.popt.topt.pager);
		else if (strcmp(opt0, "options") == 0)
			usage(pset.popt.topt.pager);
		else if (strcmp(opt0, "variables") == 0)
			helpVariables(pset.popt.topt.pager);
		else
			slashUsage(pset.popt.topt.pager);

		if (opt0)
			free(opt0);
	}
	else
		ignore_slash_options(scan_state);

	return PSQL_CMD_SKIP_LINE;
}