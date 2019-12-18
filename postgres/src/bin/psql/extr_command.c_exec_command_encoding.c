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
struct TYPE_4__ {int /*<<< orphan*/  encoding; } ;
struct TYPE_5__ {TYPE_1__ topt; } ;
struct TYPE_6__ {int /*<<< orphan*/  encoding; int /*<<< orphan*/  vars; TYPE_2__ popt; int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PQclientEncoding (int /*<<< orphan*/ ) ; 
 int PQsetClientEncoding (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_encoding_to_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 TYPE_3__ pset ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static backslashResult
exec_command_encoding(PsqlScanState scan_state, bool active_branch)
{
	if (active_branch)
	{
		char	   *encoding = psql_scan_slash_option(scan_state,
													  OT_NORMAL, NULL, false);

		if (!encoding)
		{
			/* show encoding */
			puts(pg_encoding_to_char(pset.encoding));
		}
		else
		{
			/* set encoding */
			if (PQsetClientEncoding(pset.db, encoding) == -1)
				pg_log_error("%s: invalid encoding name or conversion procedure not found", encoding);
			else
			{
				/* save encoding info into psql internal data */
				pset.encoding = PQclientEncoding(pset.db);
				pset.popt.topt.encoding = pset.encoding;
				SetVariable(pset.vars, "ENCODING",
							pg_encoding_to_char(pset.encoding));
			}
			free(encoding);
		}
	}
	else
		ignore_slash_options(scan_state);

	return PSQL_CMD_SKIP_LINE;
}