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
struct TYPE_2__ {int /*<<< orphan*/  comp_case; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSQL_COMP_CASE_LOWER ; 
 int /*<<< orphan*/  PSQL_COMP_CASE_PRESERVE_LOWER ; 
 int /*<<< orphan*/  PSQL_COMP_CASE_PRESERVE_UPPER ; 
 int /*<<< orphan*/  PSQL_COMP_CASE_UPPER ; 
 int /*<<< orphan*/  PsqlVarEnumError (char*,char const*,char*) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static bool
comp_keyword_case_hook(const char *newval)
{
	Assert(newval != NULL);		/* else substitute hook messed up */
	if (pg_strcasecmp(newval, "preserve-upper") == 0)
		pset.comp_case = PSQL_COMP_CASE_PRESERVE_UPPER;
	else if (pg_strcasecmp(newval, "preserve-lower") == 0)
		pset.comp_case = PSQL_COMP_CASE_PRESERVE_LOWER;
	else if (pg_strcasecmp(newval, "upper") == 0)
		pset.comp_case = PSQL_COMP_CASE_UPPER;
	else if (pg_strcasecmp(newval, "lower") == 0)
		pset.comp_case = PSQL_COMP_CASE_LOWER;
	else
	{
		PsqlVarEnumError("COMP_KEYWORD_CASE", newval,
						 "lower, upper, preserve-lower, preserve-upper");
		return false;
	}
	return true;
}