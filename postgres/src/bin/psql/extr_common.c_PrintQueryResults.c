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
struct TYPE_2__ {int /*<<< orphan*/  queryFout; int /*<<< orphan*/  crosstab_flag; int /*<<< orphan*/  gexec_flag; int /*<<< orphan*/  gset_prefix; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int ExecQueryTuples (int /*<<< orphan*/ *) ; 
#define  PGRES_BAD_RESPONSE 135 
#define  PGRES_COMMAND_OK 134 
#define  PGRES_COPY_IN 133 
#define  PGRES_COPY_OUT 132 
#define  PGRES_EMPTY_QUERY 131 
#define  PGRES_FATAL_ERROR 130 
#define  PGRES_NONFATAL_ERROR 129 
#define  PGRES_TUPLES_OK 128 
 char* PQcmdStatus (int /*<<< orphan*/ *) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintQueryStatus (int /*<<< orphan*/ *) ; 
 int PrintQueryTuples (int /*<<< orphan*/ *) ; 
 int PrintResultsInCrosstab (int /*<<< orphan*/ *) ; 
 int StoreQueryTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,int) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static bool
PrintQueryResults(PGresult *results)
{
	bool		success;
	const char *cmdstatus;

	if (!results)
		return false;

	switch (PQresultStatus(results))
	{
		case PGRES_TUPLES_OK:
			/* store or execute or print the data ... */
			if (pset.gset_prefix)
				success = StoreQueryTuple(results);
			else if (pset.gexec_flag)
				success = ExecQueryTuples(results);
			else if (pset.crosstab_flag)
				success = PrintResultsInCrosstab(results);
			else
				success = PrintQueryTuples(results);
			/* if it's INSERT/UPDATE/DELETE RETURNING, also print status */
			cmdstatus = PQcmdStatus(results);
			if (strncmp(cmdstatus, "INSERT", 6) == 0 ||
				strncmp(cmdstatus, "UPDATE", 6) == 0 ||
				strncmp(cmdstatus, "DELETE", 6) == 0)
				PrintQueryStatus(results);
			break;

		case PGRES_COMMAND_OK:
			PrintQueryStatus(results);
			success = true;
			break;

		case PGRES_EMPTY_QUERY:
			success = true;
			break;

		case PGRES_COPY_OUT:
		case PGRES_COPY_IN:
			/* nothing to do here */
			success = true;
			break;

		case PGRES_BAD_RESPONSE:
		case PGRES_NONFATAL_ERROR:
		case PGRES_FATAL_ERROR:
			success = false;
			break;

		default:
			success = false;
			pg_log_error("unexpected PQresultStatus: %d",
						 PQresultStatus(results));
			break;
	}

	fflush(pset.queryFout);

	return success;
}