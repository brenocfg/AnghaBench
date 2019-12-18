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
struct TYPE_2__ {char* gset_prefix; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_SEND ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 char* pg_strdup (char*) ; 
 TYPE_1__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static backslashResult
exec_command_gset(PsqlScanState scan_state, bool active_branch)
{
	backslashResult status = PSQL_CMD_SKIP_LINE;

	if (active_branch)
	{
		char	   *prefix = psql_scan_slash_option(scan_state,
													OT_NORMAL, NULL, false);

		if (prefix)
			pset.gset_prefix = prefix;
		else
		{
			/* we must set a non-NULL prefix to trigger storing */
			pset.gset_prefix = pg_strdup("");
		}
		/* gset_prefix is freed later */
		status = PSQL_CMD_SEND;
	}
	else
		ignore_slash_options(scan_state);

	return status;
}