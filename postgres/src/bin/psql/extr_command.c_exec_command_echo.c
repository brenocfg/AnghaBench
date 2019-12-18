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
struct TYPE_2__ {int /*<<< orphan*/ * queryFout; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 TYPE_1__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static backslashResult
exec_command_echo(PsqlScanState scan_state, bool active_branch, const char *cmd)
{
	if (active_branch)
	{
		char	   *value;
		char		quoted;
		bool		no_newline = false;
		bool		first = true;
		FILE	   *fout;

		if (strcmp(cmd, "qecho") == 0)
			fout = pset.queryFout;
		else if (strcmp(cmd, "warn") == 0)
			fout = stderr;
		else
			fout = stdout;

		while ((value = psql_scan_slash_option(scan_state,
											   OT_NORMAL, &quoted, false)))
		{
			if (first && !no_newline && !quoted && strcmp(value, "-n") == 0)
				no_newline = true;
			else
			{
				if (first)
					first = false;
				else
					fputc(' ', fout);
				fputs(value, fout);
			}
			free(value);
		}
		if (!no_newline)
			fputs("\n", fout);
	}
	else
		ignore_slash_options(scan_state);

	return PSQL_CMD_SKIP_LINE;
}