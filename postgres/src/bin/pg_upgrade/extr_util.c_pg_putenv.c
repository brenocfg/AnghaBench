#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  SetEnvironmentVariableA (char const*,char const*) ; 
 char* psprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  unsetenv (char const*) ; 

void
pg_putenv(const char *var, const char *val)
{
	if (val)
	{
#ifndef WIN32
		char	   *envstr;

		envstr = psprintf("%s=%s", var, val);
		putenv(envstr);

		/*
		 * Do not free envstr because it becomes part of the environment on
		 * some operating systems.  See port/unsetenv.c::unsetenv.
		 */
#else
		SetEnvironmentVariableA(var, val);
#endif
	}
	else
	{
#ifndef WIN32
		unsetenv(var);
#else
		SetEnvironmentVariableA(var, "");
#endif
	}
}