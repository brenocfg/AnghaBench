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
struct TYPE_2__ {int /*<<< orphan*/  vars; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 char* PQcmdTuples (int /*<<< orphan*/ *) ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static void
SetResultVariables(PGresult *results, bool success)
{
	if (success)
	{
		const char *ntuples = PQcmdTuples(results);

		SetVariable(pset.vars, "ERROR", "false");
		SetVariable(pset.vars, "SQLSTATE", "00000");
		SetVariable(pset.vars, "ROW_COUNT", *ntuples ? ntuples : "0");
	}
	else
	{
		const char *code = PQresultErrorField(results, PG_DIAG_SQLSTATE);
		const char *mesg = PQresultErrorField(results, PG_DIAG_MESSAGE_PRIMARY);

		SetVariable(pset.vars, "ERROR", "true");

		/*
		 * If there is no SQLSTATE code, use an empty string.  This can happen
		 * for libpq-detected errors (e.g., lost connection, ENOMEM).
		 */
		if (code == NULL)
			code = "";
		SetVariable(pset.vars, "SQLSTATE", code);
		SetVariable(pset.vars, "ROW_COUNT", "0");
		SetVariable(pset.vars, "LAST_ERROR_SQLSTATE", code);
		SetVariable(pset.vars, "LAST_ERROR_MESSAGE", mesg ? mesg : "");
	}
}