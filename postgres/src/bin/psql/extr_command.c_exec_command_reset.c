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
struct TYPE_2__ {int /*<<< orphan*/  quiet; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  psql_scan_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static backslashResult
exec_command_reset(PsqlScanState scan_state, bool active_branch,
				   PQExpBuffer query_buf)
{
	if (active_branch)
	{
		resetPQExpBuffer(query_buf);
		psql_scan_reset(scan_state);
		if (!pset.quiet)
			puts(_("Query buffer reset (cleared)."));
	}

	return PSQL_CMD_SKIP_LINE;
}