#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * last_res; int /*<<< orphan*/ * cur_res; } ;
typedef  TYPE_1__ storeInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PGRES_SINGLE_TUPLE ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQsendQuery (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  PQsetSingleRowMode (int /*<<< orphan*/ *) ; 
 int applyRemoteGucs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pchomp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restoreLocalGucs (int) ; 
 int /*<<< orphan*/  storeRow (TYPE_1__ volatile*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static PGresult *
storeQueryResult(volatile storeInfo *sinfo, PGconn *conn, const char *sql)
{
	bool		first = true;
	int			nestlevel = -1;
	PGresult   *res;

	if (!PQsendQuery(conn, sql))
		elog(ERROR, "could not send query: %s", pchomp(PQerrorMessage(conn)));

	if (!PQsetSingleRowMode(conn))	/* shouldn't fail */
		elog(ERROR, "failed to set single-row mode for dblink query");

	for (;;)
	{
		CHECK_FOR_INTERRUPTS();

		sinfo->cur_res = PQgetResult(conn);
		if (!sinfo->cur_res)
			break;

		if (PQresultStatus(sinfo->cur_res) == PGRES_SINGLE_TUPLE)
		{
			/* got one row from possibly-bigger resultset */

			/*
			 * Set GUCs to ensure we read GUC-sensitive data types correctly.
			 * We shouldn't do this until we have a row in hand, to ensure
			 * libpq has seen any earlier ParameterStatus protocol messages.
			 */
			if (first && nestlevel < 0)
				nestlevel = applyRemoteGucs(conn);

			storeRow(sinfo, sinfo->cur_res, first);

			PQclear(sinfo->cur_res);
			sinfo->cur_res = NULL;
			first = false;
		}
		else
		{
			/* if empty resultset, fill tuplestore header */
			if (first && PQresultStatus(sinfo->cur_res) == PGRES_TUPLES_OK)
				storeRow(sinfo, sinfo->cur_res, first);

			/* store completed result at last_res */
			PQclear(sinfo->last_res);
			sinfo->last_res = sinfo->cur_res;
			sinfo->cur_res = NULL;
			first = true;
		}
	}

	/* clean up GUC settings, if we changed any */
	restoreLocalGucs(nestlevel);

	/* return last_res */
	res = sinfo->last_res;
	sinfo->last_res = NULL;
	return res;
}