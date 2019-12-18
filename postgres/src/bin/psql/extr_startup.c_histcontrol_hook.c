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
struct TYPE_2__ {int /*<<< orphan*/  histcontrol; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PsqlVarEnumError (char*,char const*,char*) ; 
 int /*<<< orphan*/  hctl_ignoreboth ; 
 int /*<<< orphan*/  hctl_ignoredups ; 
 int /*<<< orphan*/  hctl_ignorespace ; 
 int /*<<< orphan*/  hctl_none ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static bool
histcontrol_hook(const char *newval)
{
	Assert(newval != NULL);		/* else substitute hook messed up */
	if (pg_strcasecmp(newval, "ignorespace") == 0)
		pset.histcontrol = hctl_ignorespace;
	else if (pg_strcasecmp(newval, "ignoredups") == 0)
		pset.histcontrol = hctl_ignoredups;
	else if (pg_strcasecmp(newval, "ignoreboth") == 0)
		pset.histcontrol = hctl_ignoreboth;
	else if (pg_strcasecmp(newval, "none") == 0)
		pset.histcontrol = hctl_none;
	else
	{
		PsqlVarEnumError("HISTCONTROL", newval,
						 "none, ignorespace, ignoredups, ignoreboth");
		return false;
	}
	return true;
}