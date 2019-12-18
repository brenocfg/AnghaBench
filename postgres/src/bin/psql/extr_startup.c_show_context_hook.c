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
struct TYPE_2__ {int /*<<< orphan*/  show_context; scalar_t__ db; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQSHOW_CONTEXT_ALWAYS ; 
 int /*<<< orphan*/  PQSHOW_CONTEXT_ERRORS ; 
 int /*<<< orphan*/  PQSHOW_CONTEXT_NEVER ; 
 int /*<<< orphan*/  PQsetErrorContextVisibility (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PsqlVarEnumError (char*,char const*,char*) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static bool
show_context_hook(const char *newval)
{
	Assert(newval != NULL);		/* else substitute hook messed up */
	if (pg_strcasecmp(newval, "never") == 0)
		pset.show_context = PQSHOW_CONTEXT_NEVER;
	else if (pg_strcasecmp(newval, "errors") == 0)
		pset.show_context = PQSHOW_CONTEXT_ERRORS;
	else if (pg_strcasecmp(newval, "always") == 0)
		pset.show_context = PQSHOW_CONTEXT_ALWAYS;
	else
	{
		PsqlVarEnumError("SHOW_CONTEXT", newval, "never, errors, always");
		return false;
	}

	if (pset.db)
		PQsetErrorContextVisibility(pset.db, pset.show_context);
	return true;
}