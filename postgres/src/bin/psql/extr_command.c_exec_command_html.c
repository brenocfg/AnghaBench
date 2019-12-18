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
struct TYPE_4__ {scalar_t__ format; } ;
struct TYPE_6__ {TYPE_1__ topt; } ;
struct TYPE_5__ {int /*<<< orphan*/  quiet; TYPE_3__ popt; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 scalar_t__ PRINT_HTML ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int do_pset (char*,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ pset ; 

__attribute__((used)) static backslashResult
exec_command_html(PsqlScanState scan_state, bool active_branch)
{
	bool		success = true;

	if (active_branch)
	{
		if (pset.popt.topt.format != PRINT_HTML)
			success = do_pset("format", "html", &pset.popt, pset.quiet);
		else
			success = do_pset("format", "aligned", &pset.popt, pset.quiet);
	}

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}