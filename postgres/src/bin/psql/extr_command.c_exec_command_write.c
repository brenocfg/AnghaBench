#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  backslashResult ;
struct TYPE_4__ {scalar_t__ len; char* data; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  OT_FILEPIPE ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/  disable_sigpipe_trap () ; 
 int /*<<< orphan*/  expand_tilde (char**) ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_filepipe (int /*<<< orphan*/ ) ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  restore_sigpipe_trap () ; 

__attribute__((used)) static backslashResult
exec_command_write(PsqlScanState scan_state, bool active_branch,
				   const char *cmd,
				   PQExpBuffer query_buf, PQExpBuffer previous_buf)
{
	backslashResult status = PSQL_CMD_SKIP_LINE;

	if (active_branch)
	{
		char	   *fname = psql_scan_slash_option(scan_state,
												   OT_FILEPIPE, NULL, true);
		FILE	   *fd = NULL;
		bool		is_pipe = false;

		if (!query_buf)
		{
			pg_log_error("no query buffer");
			status = PSQL_CMD_ERROR;
		}
		else
		{
			if (!fname)
			{
				pg_log_error("\\%s: missing required argument", cmd);
				status = PSQL_CMD_ERROR;
			}
			else
			{
				expand_tilde(&fname);
				if (fname[0] == '|')
				{
					is_pipe = true;
					disable_sigpipe_trap();
					fd = popen(&fname[1], "w");
				}
				else
				{
					canonicalize_path(fname);
					fd = fopen(fname, "w");
				}
				if (!fd)
				{
					pg_log_error("%s: %m", fname);
					status = PSQL_CMD_ERROR;
				}
			}
		}

		if (fd)
		{
			int			result;

			/*
			 * We want to print the same thing \g would execute, but not to
			 * change the query buffer state; so we can't use
			 * copy_previous_query().  Also, beware of possibility that buffer
			 * pointers are NULL.
			 */
			if (query_buf && query_buf->len > 0)
				fprintf(fd, "%s\n", query_buf->data);
			else if (previous_buf && previous_buf->len > 0)
				fprintf(fd, "%s\n", previous_buf->data);

			if (is_pipe)
				result = pclose(fd);
			else
				result = fclose(fd);

			if (result == EOF)
			{
				pg_log_error("%s: %m", fname);
				status = PSQL_CMD_ERROR;
			}
		}

		if (is_pipe)
			restore_sigpipe_trap();

		free(fname);
	}
	else
		ignore_slash_filepipe(scan_state);

	return status;
}