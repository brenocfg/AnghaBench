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
struct TYPE_2__ {int /*<<< orphan*/  vars; int /*<<< orphan*/  gset_prefix; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 char* PQfname (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 char* PQgetvalue (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int PQnfields (int /*<<< orphan*/  const*) ; 
 int PQntuples (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 TYPE_1__ pset ; 
 char* psprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
StoreQueryTuple(const PGresult *result)
{
	bool		success = true;

	if (PQntuples(result) < 1)
	{
		pg_log_error("no rows returned for \\gset");
		success = false;
	}
	else if (PQntuples(result) > 1)
	{
		pg_log_error("more than one row returned for \\gset");
		success = false;
	}
	else
	{
		int			i;

		for (i = 0; i < PQnfields(result); i++)
		{
			char	   *colname = PQfname(result, i);
			char	   *varname;
			char	   *value;

			/* concatenate prefix and column name */
			varname = psprintf("%s%s", pset.gset_prefix, colname);

			if (!PQgetisnull(result, 0, i))
				value = PQgetvalue(result, 0, i);
			else
			{
				/* for NULL value, unset rather than set the variable */
				value = NULL;
			}

			if (!SetVariable(pset.vars, varname, value))
			{
				free(varname);
				success = false;
				break;
			}

			free(varname);
		}
	}

	return success;
}