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
struct statement {scalar_t__ nparams; scalar_t__ statement_type; int /*<<< orphan*/  compat; TYPE_1__* connection; int /*<<< orphan*/  lineno; int /*<<< orphan*/  results; scalar_t__ paramformats; scalar_t__ paramlengths; scalar_t__ paramvalues; int /*<<< orphan*/  command; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  connection; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ECPGst_execute ; 
 scalar_t__ ECPGst_prepare ; 
 int /*<<< orphan*/  PQexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQexecParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,char const* const*,int const*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQexecPrepared (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char const* const*,int const*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_check_PQresult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_free_params (struct statement*,int) ; 
 int /*<<< orphan*/  ecpg_log (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ecpg_register_prepared_stmt (struct statement*) ; 

bool
ecpg_execute(struct statement *stmt)
{
	ecpg_log("ecpg_execute on line %d: query: %s; with %d parameter(s) on connection %s\n", stmt->lineno, stmt->command, stmt->nparams, stmt->connection->name);
	if (stmt->statement_type == ECPGst_execute)
	{
		stmt->results = PQexecPrepared(stmt->connection->connection,
									   stmt->name,
									   stmt->nparams,
									   (const char *const *) stmt->paramvalues,
									   (const int *) stmt->paramlengths,
									   (const int *) stmt->paramformats,
									   0);
		ecpg_log("ecpg_execute on line %d: using PQexecPrepared for \"%s\"\n", stmt->lineno, stmt->command);
	}
	else
	{
		if (stmt->nparams == 0)
		{
			stmt->results = PQexec(stmt->connection->connection, stmt->command);
			ecpg_log("ecpg_execute on line %d: using PQexec\n", stmt->lineno);
		}
		else
		{
			stmt->results = PQexecParams(stmt->connection->connection,
										 stmt->command, stmt->nparams, NULL,
										 (const char *const *) stmt->paramvalues,
										 (const int *) stmt->paramlengths,
										 (const int *) stmt->paramformats,
										 0);

			ecpg_log("ecpg_execute on line %d: using PQexecParams\n", stmt->lineno);
		}

		if (stmt->statement_type == ECPGst_prepare)
		{
			if (!ecpg_register_prepared_stmt(stmt))
			{
				ecpg_free_params(stmt, true);
				return false;
			}
		}
	}

	ecpg_free_params(stmt, true);

	if (!ecpg_check_PQresult(stmt->results, stmt->lineno, stmt->connection->connection, stmt->compat))
		return false;

	return true;
}