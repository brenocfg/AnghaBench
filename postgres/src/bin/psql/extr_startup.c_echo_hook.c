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
struct TYPE_2__ {int /*<<< orphan*/  echo; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSQL_ECHO_ALL ; 
 int /*<<< orphan*/  PSQL_ECHO_ERRORS ; 
 int /*<<< orphan*/  PSQL_ECHO_NONE ; 
 int /*<<< orphan*/  PSQL_ECHO_QUERIES ; 
 int /*<<< orphan*/  PsqlVarEnumError (char*,char const*,char*) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static bool
echo_hook(const char *newval)
{
	Assert(newval != NULL);		/* else substitute hook messed up */
	if (pg_strcasecmp(newval, "queries") == 0)
		pset.echo = PSQL_ECHO_QUERIES;
	else if (pg_strcasecmp(newval, "errors") == 0)
		pset.echo = PSQL_ECHO_ERRORS;
	else if (pg_strcasecmp(newval, "all") == 0)
		pset.echo = PSQL_ECHO_ALL;
	else if (pg_strcasecmp(newval, "none") == 0)
		pset.echo = PSQL_ECHO_NONE;
	else
	{
		PsqlVarEnumError("ECHO", newval, "none, errors, queries, all");
		return false;
	}
	return true;
}