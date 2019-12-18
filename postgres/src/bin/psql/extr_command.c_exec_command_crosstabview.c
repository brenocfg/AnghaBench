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
struct TYPE_2__ {int crosstab_flag; int /*<<< orphan*/ * ctv_args; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_SEND ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int lengthof (int /*<<< orphan*/ *) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static backslashResult
exec_command_crosstabview(PsqlScanState scan_state, bool active_branch)
{
	backslashResult status = PSQL_CMD_SKIP_LINE;

	if (active_branch)
	{
		int			i;

		for (i = 0; i < lengthof(pset.ctv_args); i++)
			pset.ctv_args[i] = psql_scan_slash_option(scan_state,
													  OT_NORMAL, NULL, true);
		pset.crosstab_flag = true;
		status = PSQL_CMD_SEND;
	}
	else
		ignore_slash_options(scan_state);

	return status;
}