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
struct TYPE_2__ {scalar_t__ last_error_result; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  PQERRORS_VERBOSE ; 
 int /*<<< orphan*/  PQSHOW_CONTEXT_ALWAYS ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 char* PQresultVerboseErrorMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static backslashResult
exec_command_errverbose(PsqlScanState scan_state, bool active_branch)
{
	if (active_branch)
	{
		if (pset.last_error_result)
		{
			char	   *msg;

			msg = PQresultVerboseErrorMessage(pset.last_error_result,
											  PQERRORS_VERBOSE,
											  PQSHOW_CONTEXT_ALWAYS);
			if (msg)
			{
				pg_log_error("%s", msg);
				PQfreemem(msg);
			}
			else
				puts(_("out of memory"));
		}
		else
			puts(_("There is no previous error."));
	}

	return PSQL_CMD_SKIP_LINE;
}