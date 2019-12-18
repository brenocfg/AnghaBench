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
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  copy_previous_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_watch (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psql_scan_reset (int /*<<< orphan*/ ) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ ) ; 
 double strtod (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static backslashResult
exec_command_watch(PsqlScanState scan_state, bool active_branch,
				   PQExpBuffer query_buf, PQExpBuffer previous_buf)
{
	bool		success = true;

	if (active_branch)
	{
		char	   *opt = psql_scan_slash_option(scan_state,
												 OT_NORMAL, NULL, true);
		double		sleep = 2;

		/* Convert optional sleep-length argument */
		if (opt)
		{
			sleep = strtod(opt, NULL);
			if (sleep <= 0)
				sleep = 1;
			free(opt);
		}

		/* If query_buf is empty, recall and execute previous query */
		copy_previous_query(query_buf, previous_buf);

		success = do_watch(query_buf, sleep);

		/* Reset the query buffer as though for \r */
		resetPQExpBuffer(query_buf);
		psql_scan_reset(scan_state);
	}
	else
		ignore_slash_options(scan_state);

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}