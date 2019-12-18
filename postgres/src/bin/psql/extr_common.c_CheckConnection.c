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
struct TYPE_2__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  cur_cmd_interactive; } ;

/* Variables and functions */
 int ConnectionUp () ; 
 int /*<<< orphan*/  EXIT_BADCONN ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQreset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SyncVariables () ; 
 int /*<<< orphan*/  UnsyncVariables () ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  connection_warnings (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_log_fatal (char*) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool
CheckConnection(void)
{
	bool		OK;

	OK = ConnectionUp();
	if (!OK)
	{
		if (!pset.cur_cmd_interactive)
		{
			pg_log_fatal("connection to server was lost");
			exit(EXIT_BADCONN);
		}

		fprintf(stderr, _("The connection to the server was lost. Attempting reset: "));
		PQreset(pset.db);
		OK = ConnectionUp();
		if (!OK)
		{
			fprintf(stderr, _("Failed.\n"));

			/*
			 * Transition to having no connection.  Keep this bit in sync with
			 * do_connect().
			 */
			PQfinish(pset.db);
			pset.db = NULL;
			ResetCancelConn();
			UnsyncVariables();
		}
		else
		{
			fprintf(stderr, _("Succeeded.\n"));

			/*
			 * Re-sync, just in case anything changed.  Keep this in sync with
			 * do_connect().
			 */
			SyncVariables();
			connection_warnings(false); /* Must be after SyncVariables */
		}
	}

	return OK;
}