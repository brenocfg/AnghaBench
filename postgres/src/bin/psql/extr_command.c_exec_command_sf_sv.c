#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sverbuf ;
typedef  int /*<<< orphan*/  backslashResult ;
struct TYPE_8__ {int /*<<< orphan*/  topt; } ;
struct TYPE_10__ {int sversion; int /*<<< orphan*/ * queryFout; TYPE_1__ popt; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EditableObjectType ;

/* Variables and functions */
 int /*<<< orphan*/  ClosePager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EditableFunction ; 
 int /*<<< orphan*/  EditableView ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OT_WHOLE_LINE ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/ * PageOutput (int,int /*<<< orphan*/ *) ; 
 int count_lines_in_buf (TYPE_2__*) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_create_object_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ignore_slash_whole_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_object_oid (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  print_with_linenumbers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

__attribute__((used)) static backslashResult
exec_command_sf_sv(PsqlScanState scan_state, bool active_branch,
				   const char *cmd, bool is_func)
{
	backslashResult status = PSQL_CMD_SKIP_LINE;

	if (active_branch)
	{
		bool		show_linenumbers = (strchr(cmd, '+') != NULL);
		PQExpBuffer buf;
		char	   *obj_desc;
		Oid			obj_oid = InvalidOid;
		EditableObjectType eot = is_func ? EditableFunction : EditableView;

		buf = createPQExpBuffer();
		obj_desc = psql_scan_slash_option(scan_state,
										  OT_WHOLE_LINE, NULL, true);
		if (pset.sversion < (is_func ? 80400 : 70400))
		{
			char		sverbuf[32];

			formatPGVersionNumber(pset.sversion, false,
								  sverbuf, sizeof(sverbuf));
			if (is_func)
				pg_log_error("The server (version %s) does not support showing function source.",
							 sverbuf);
			else
				pg_log_error("The server (version %s) does not support showing view definitions.",
							 sverbuf);
			status = PSQL_CMD_ERROR;
		}
		else if (!obj_desc)
		{
			if (is_func)
				pg_log_error("function name is required");
			else
				pg_log_error("view name is required");
			status = PSQL_CMD_ERROR;
		}
		else if (!lookup_object_oid(eot, obj_desc, &obj_oid))
		{
			/* error already reported */
			status = PSQL_CMD_ERROR;
		}
		else if (!get_create_object_cmd(eot, obj_oid, buf))
		{
			/* error already reported */
			status = PSQL_CMD_ERROR;
		}
		else
		{
			FILE	   *output;
			bool		is_pager;

			/* Select output stream: stdout, pager, or file */
			if (pset.queryFout == stdout)
			{
				/* count lines in function to see if pager is needed */
				int			lineno = count_lines_in_buf(buf);

				output = PageOutput(lineno, &(pset.popt.topt));
				is_pager = true;
			}
			else
			{
				/* use previously set output file, without pager */
				output = pset.queryFout;
				is_pager = false;
			}

			if (show_linenumbers)
			{
				/*
				 * For functions, lineno "1" should correspond to the first
				 * line of the function body.  We expect that
				 * pg_get_functiondef() will emit that on a line beginning
				 * with "AS ", and that there can be no such line before the
				 * real start of the function body.
				 */
				print_with_linenumbers(output, buf->data,
									   is_func ? "AS " : NULL);
			}
			else
			{
				/* just send the definition to output */
				fputs(buf->data, output);
			}

			if (is_pager)
				ClosePager(output);
		}

		if (obj_desc)
			free(obj_desc);
		destroyPQExpBuffer(buf);
	}
	else
		ignore_slash_whole_line(scan_state);

	return status;
}