#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sql ;
struct TYPE_6__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;
struct TYPE_9__ {TYPE_2__ ss; scalar_t__ fdw_state; } ;
struct TYPE_8__ {int cursor_exists; int cursor_number; int fetch_ct_2; int eof_reached; scalar_t__ next_tuple; scalar_t__ num_tuples; int /*<<< orphan*/ * tuples; int /*<<< orphan*/  conn; } ;
typedef  TYPE_3__ PgFdwScanState ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ ForeignScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgfdw_exec_query (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pgfdw_report_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
postgresReScanForeignScan(ForeignScanState *node)
{
	PgFdwScanState *fsstate = (PgFdwScanState *) node->fdw_state;
	char		sql[64];
	PGresult   *res;

	/* If we haven't created the cursor yet, nothing to do. */
	if (!fsstate->cursor_exists)
		return;

	/*
	 * If any internal parameters affecting this node have changed, we'd
	 * better destroy and recreate the cursor.  Otherwise, rewinding it should
	 * be good enough.  If we've only fetched zero or one batch, we needn't
	 * even rewind the cursor, just rescan what we have.
	 */
	if (node->ss.ps.chgParam != NULL)
	{
		fsstate->cursor_exists = false;
		snprintf(sql, sizeof(sql), "CLOSE c%u",
				 fsstate->cursor_number);
	}
	else if (fsstate->fetch_ct_2 > 1)
	{
		snprintf(sql, sizeof(sql), "MOVE BACKWARD ALL IN c%u",
				 fsstate->cursor_number);
	}
	else
	{
		/* Easy: just rescan what we already have in memory, if anything */
		fsstate->next_tuple = 0;
		return;
	}

	/*
	 * We don't use a PG_TRY block here, so be careful not to throw error
	 * without releasing the PGresult.
	 */
	res = pgfdw_exec_query(fsstate->conn, sql);
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
		pgfdw_report_error(ERROR, res, fsstate->conn, true, sql);
	PQclear(res);

	/* Now force a fresh FETCH. */
	fsstate->tuples = NULL;
	fsstate->num_tuples = 0;
	fsstate->next_tuple = 0;
	fsstate->fetch_ct_2 = 0;
	fsstate->eof_reached = false;
}