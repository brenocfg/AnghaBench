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
typedef  int /*<<< orphan*/  prefix ;
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
typedef  int /*<<< orphan*/  backslashResult ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int ParseVariableBool (char*,char*,int*) ; 
 int TRI_DEFAULT ; 
 int TRI_NO ; 
 int TRI_YES ; 
 int do_connect (int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 char* read_connect_arg (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static backslashResult
exec_command_connect(PsqlScanState scan_state, bool active_branch)
{
	bool		success = true;

	if (active_branch)
	{
		static const char prefix[] = "-reuse-previous=";
		char	   *opt1,
				   *opt2,
				   *opt3,
				   *opt4;
		enum trivalue reuse_previous = TRI_DEFAULT;

		opt1 = read_connect_arg(scan_state);
		if (opt1 != NULL && strncmp(opt1, prefix, sizeof(prefix) - 1) == 0)
		{
			bool		on_off;

			success = ParseVariableBool(opt1 + sizeof(prefix) - 1,
										"-reuse-previous",
										&on_off);
			if (success)
			{
				reuse_previous = on_off ? TRI_YES : TRI_NO;
				free(opt1);
				opt1 = read_connect_arg(scan_state);
			}
		}

		if (success)			/* give up if reuse_previous was invalid */
		{
			opt2 = read_connect_arg(scan_state);
			opt3 = read_connect_arg(scan_state);
			opt4 = read_connect_arg(scan_state);

			success = do_connect(reuse_previous, opt1, opt2, opt3, opt4);

			free(opt2);
			free(opt3);
			free(opt4);
		}
		free(opt1);
	}
	else
		ignore_slash_options(scan_state);

	return success ? PSQL_CMD_SKIP_LINE : PSQL_CMD_ERROR;
}