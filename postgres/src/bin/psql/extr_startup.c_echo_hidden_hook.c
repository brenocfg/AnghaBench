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
struct TYPE_2__ {int /*<<< orphan*/  echo_hidden; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSQL_ECHO_HIDDEN_NOEXEC ; 
 int /*<<< orphan*/  PSQL_ECHO_HIDDEN_OFF ; 
 int /*<<< orphan*/  PSQL_ECHO_HIDDEN_ON ; 
 scalar_t__ ParseVariableBool (char const*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  PsqlVarEnumError (char*,char const*,char*) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static bool
echo_hidden_hook(const char *newval)
{
	Assert(newval != NULL);		/* else substitute hook messed up */
	if (pg_strcasecmp(newval, "noexec") == 0)
		pset.echo_hidden = PSQL_ECHO_HIDDEN_NOEXEC;
	else
	{
		bool		on_off;

		if (ParseVariableBool(newval, NULL, &on_off))
			pset.echo_hidden = on_off ? PSQL_ECHO_HIDDEN_ON : PSQL_ECHO_HIDDEN_OFF;
		else
		{
			PsqlVarEnumError("ECHO_HIDDEN", newval, "on, off, noexec");
			return false;
		}
	}
	return true;
}