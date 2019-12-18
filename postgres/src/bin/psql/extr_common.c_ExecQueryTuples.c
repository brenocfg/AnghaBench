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
struct TYPE_2__ {int gexec_flag; scalar_t__ echo; scalar_t__ on_error_stop; int /*<<< orphan*/  singlestep; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/  const*,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/  const*,int,int) ; 
 int PQnfields (int /*<<< orphan*/  const*) ; 
 int PQntuples (int /*<<< orphan*/  const*) ; 
 scalar_t__ PSQL_ECHO_ALL ; 
 int /*<<< orphan*/  SendQuery (char const*) ; 
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  puts (char const*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static bool
ExecQueryTuples(const PGresult *result)
{
	bool		success = true;
	int			nrows = PQntuples(result);
	int			ncolumns = PQnfields(result);
	int			r,
				c;

	/*
	 * We must turn off gexec_flag to avoid infinite recursion.  Note that
	 * this allows ExecQueryUsingCursor to be applied to the individual query
	 * results.  SendQuery prevents it from being applied when fetching the
	 * queries-to-execute, because it can't handle recursion either.
	 */
	pset.gexec_flag = false;

	for (r = 0; r < nrows; r++)
	{
		for (c = 0; c < ncolumns; c++)
		{
			if (!PQgetisnull(result, r, c))
			{
				const char *query = PQgetvalue(result, r, c);

				/* Abandon execution if cancel_pressed */
				if (cancel_pressed)
					goto loop_exit;

				/*
				 * ECHO_ALL mode should echo these queries, but SendQuery
				 * assumes that MainLoop did that, so we have to do it here.
				 */
				if (pset.echo == PSQL_ECHO_ALL && !pset.singlestep)
				{
					puts(query);
					fflush(stdout);
				}

				if (!SendQuery(query))
				{
					/* Error - abandon execution if ON_ERROR_STOP */
					success = false;
					if (pset.on_error_stop)
						goto loop_exit;
				}
			}
		}
	}

loop_exit:

	/*
	 * Restore state.  We know gexec_flag was on, else we'd not be here. (We
	 * also know it'll get turned off at end of command, but that's not ours
	 * to do here.)
	 */
	pset.gexec_flag = true;

	/* Return true if all queries were successful */
	return success;
}