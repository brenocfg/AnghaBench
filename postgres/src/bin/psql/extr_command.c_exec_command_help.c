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
 int /*<<< orphan*/  OT_WHOLE_LINE ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  helpSQL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_slash_whole_line (int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (unsigned char) ; 
 TYPE_3__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static backslashResult
exec_command_help(PsqlScanState scan_state, bool active_branch)
{
	if (active_branch)
	{
		char	   *opt = psql_scan_slash_option(scan_state,
												 OT_WHOLE_LINE, NULL, false);
		size_t		len;

		/* strip any trailing spaces and semicolons */
		if (opt)
		{
			len = strlen(opt);
			while (len > 0 &&
				   (isspace((unsigned char) opt[len - 1])
					|| opt[len - 1] == ';'))
				opt[--len] = '\0';
		}

		helpSQL(opt, pset.popt.topt.pager);
		free(opt);
	}
	else
		ignore_slash_whole_line(scan_state);

	return PSQL_CMD_SKIP_LINE;
}