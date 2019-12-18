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
struct TYPE_2__ {int /*<<< orphan*/  quiet; int /*<<< orphan*/  popt; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int do_pset (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const* const,char*) ; 
 TYPE_1__ pset ; 
 char* pset_value_string (char const* const,int /*<<< orphan*/ *) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static backslashResult
exec_command_pset(PsqlScanState scan_state, bool active_branch)
{
	bool		success = true;

	if (active_branch)
	{
		char	   *opt0 = psql_scan_slash_option(scan_state,
												  OT_NORMAL, NULL, false);
		char	   *opt1 = psql_scan_slash_option(scan_state,
												  OT_NORMAL, NULL, false);

		if (!opt0)
		{
			/* list all variables */

			int			i;
			static const char *const my_list[] = {
				"border", "columns", "csv_fieldsep", "expanded", "fieldsep",
				"fieldsep_zero", "footer", "format", "linestyle", "null",
				"numericlocale", "pager", "pager_min_lines",
				"recordsep", "recordsep_zero",
				"tableattr", "title", "tuples_only",
				"unicode_border_linestyle",
				"unicode_column_linestyle",
				"unicode_header_linestyle",
				NULL
			};

			for (i = 0; my_list[i] != NULL; i++)
			{
				char	   *val = pset_value_string(my_list[i], &pset.popt);

				printf("%-24s %s\n", my_list[i], val);
				free(val);
			}

			success = true;
		}
		else
			success = do_pset(opt0, opt1, &pset.popt, pset.quiet);

		free(opt0);
		free(opt1);
	}
	else
		ignore_slash_options(scan_state);

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}