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
struct TYPE_2__ {int /*<<< orphan*/  db; int /*<<< orphan*/ * cur_cmd_source; int /*<<< orphan*/ * copyStream; int /*<<< orphan*/ * queryFout; scalar_t__ gfname; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int ExecStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckConnection () ; 
#define  PGRES_COMMAND_OK 132 
#define  PGRES_COPY_IN 131 
#define  PGRES_COPY_OUT 130 
#define  PGRES_EMPTY_QUERY 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PQbinaryTuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn () ; 
 int /*<<< orphan*/  SetResultVariables (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  disable_sigpipe_trap () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ handleCopyIn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ handleCopyOut (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ openQueryOutputFile (scalar_t__,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,int) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  restore_sigpipe_trap () ; 

__attribute__((used)) static bool
ProcessResult(PGresult **results)
{
	bool		success = true;
	bool		first_cycle = true;

	for (;;)
	{
		ExecStatusType result_status;
		bool		is_copy;
		PGresult   *next_result;

		if (!AcceptResult(*results))
		{
			/*
			 * Failure at this point is always a server-side failure or a
			 * failure to submit the command string.  Either way, we're
			 * finished with this command string.
			 */
			success = false;
			break;
		}

		result_status = PQresultStatus(*results);
		switch (result_status)
		{
			case PGRES_EMPTY_QUERY:
			case PGRES_COMMAND_OK:
			case PGRES_TUPLES_OK:
				is_copy = false;
				break;

			case PGRES_COPY_OUT:
			case PGRES_COPY_IN:
				is_copy = true;
				break;

			default:
				/* AcceptResult() should have caught anything else. */
				is_copy = false;
				pg_log_error("unexpected PQresultStatus: %d", result_status);
				break;
		}

		if (is_copy)
		{
			/*
			 * Marshal the COPY data.  Either subroutine will get the
			 * connection out of its COPY state, then call PQresultStatus()
			 * once and report any error.
			 *
			 * For COPY OUT, direct the output to pset.copyStream if it's set,
			 * otherwise to pset.gfname if it's set, otherwise to queryFout.
			 * For COPY IN, use pset.copyStream as data source if it's set,
			 * otherwise cur_cmd_source.
			 */
			FILE	   *copystream;
			PGresult   *copy_result;

			SetCancelConn();
			if (result_status == PGRES_COPY_OUT)
			{
				bool		need_close = false;
				bool		is_pipe = false;

				if (pset.copyStream)
				{
					/* invoked by \copy */
					copystream = pset.copyStream;
				}
				else if (pset.gfname)
				{
					/* invoked by \g */
					if (openQueryOutputFile(pset.gfname,
											&copystream, &is_pipe))
					{
						need_close = true;
						if (is_pipe)
							disable_sigpipe_trap();
					}
					else
						copystream = NULL;	/* discard COPY data entirely */
				}
				else
				{
					/* fall back to the generic query output stream */
					copystream = pset.queryFout;
				}

				success = handleCopyOut(pset.db,
										copystream,
										&copy_result)
					&& success
					&& (copystream != NULL);

				/*
				 * Suppress status printing if the report would go to the same
				 * place as the COPY data just went.  Note this doesn't
				 * prevent error reporting, since handleCopyOut did that.
				 */
				if (copystream == pset.queryFout)
				{
					PQclear(copy_result);
					copy_result = NULL;
				}

				if (need_close)
				{
					/* close \g argument file/pipe */
					if (is_pipe)
					{
						pclose(copystream);
						restore_sigpipe_trap();
					}
					else
					{
						fclose(copystream);
					}
				}
			}
			else
			{
				/* COPY IN */
				copystream = pset.copyStream ? pset.copyStream : pset.cur_cmd_source;
				success = handleCopyIn(pset.db,
									   copystream,
									   PQbinaryTuples(*results),
									   &copy_result) && success;
			}
			ResetCancelConn();

			/*
			 * Replace the PGRES_COPY_OUT/IN result with COPY command's exit
			 * status, or with NULL if we want to suppress printing anything.
			 */
			PQclear(*results);
			*results = copy_result;
		}
		else if (first_cycle)
		{
			/* fast path: no COPY commands; PQexec visited all results */
			break;
		}

		/*
		 * Check PQgetResult() again.  In the typical case of a single-command
		 * string, it will return NULL.  Otherwise, we'll have other results
		 * to process that may include other COPYs.  We keep the last result.
		 */
		next_result = PQgetResult(pset.db);
		if (!next_result)
			break;

		PQclear(*results);
		*results = next_result;
		first_cycle = false;
	}

	SetResultVariables(*results, success);

	/* may need this to recover from conn loss during COPY */
	if (!first_cycle && !CheckConnection())
		return false;

	return success;
}