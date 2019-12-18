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
typedef  scalar_t__ backslashResult ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 scalar_t__ PSQL_CMD_ERROR ; 
 scalar_t__ PSQL_CMD_NEWEDIT ; 
 scalar_t__ PSQL_CMD_SKIP_LINE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/  copy_previous_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ do_edit (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expand_tilde (char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 

__attribute__((used)) static backslashResult
exec_command_edit(PsqlScanState scan_state, bool active_branch,
				  PQExpBuffer query_buf, PQExpBuffer previous_buf)
{
	backslashResult status = PSQL_CMD_SKIP_LINE;

	if (active_branch)
	{
		if (!query_buf)
		{
			pg_log_error("no query buffer");
			status = PSQL_CMD_ERROR;
		}
		else
		{
			char	   *fname;
			char	   *ln = NULL;
			int			lineno = -1;

			fname = psql_scan_slash_option(scan_state,
										   OT_NORMAL, NULL, true);
			if (fname)
			{
				/* try to get separate lineno arg */
				ln = psql_scan_slash_option(scan_state,
											OT_NORMAL, NULL, true);
				if (ln == NULL)
				{
					/* only one arg; maybe it is lineno not fname */
					if (fname[0] &&
						strspn(fname, "0123456789") == strlen(fname))
					{
						/* all digits, so assume it is lineno */
						ln = fname;
						fname = NULL;
					}
				}
			}
			if (ln)
			{
				lineno = atoi(ln);
				if (lineno < 1)
				{
					pg_log_error("invalid line number: %s", ln);
					status = PSQL_CMD_ERROR;
				}
			}
			if (status != PSQL_CMD_ERROR)
			{
				expand_tilde(&fname);
				if (fname)
					canonicalize_path(fname);

				/* If query_buf is empty, recall previous query for editing */
				copy_previous_query(query_buf, previous_buf);

				if (do_edit(fname, query_buf, lineno, NULL))
					status = PSQL_CMD_NEWEDIT;
				else
					status = PSQL_CMD_ERROR;
			}
			if (fname)
				free(fname);
			if (ln)
				free(ln);
		}
	}
	else
		ignore_slash_options(scan_state);

	return status;
}