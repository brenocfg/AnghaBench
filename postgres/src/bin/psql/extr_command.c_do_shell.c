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
 char* DEFAULT_SHELL ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 char* psprintf (char*,char const*) ; 
 int system (char const*) ; 

__attribute__((used)) static bool
do_shell(const char *command)
{
	int			result;

	if (!command)
	{
		char	   *sys;
		const char *shellName;

		shellName = getenv("SHELL");
#ifdef WIN32
		if (shellName == NULL)
			shellName = getenv("COMSPEC");
#endif
		if (shellName == NULL)
			shellName = DEFAULT_SHELL;

		/* See EDITOR handling comment for an explanation */
#ifndef WIN32
		sys = psprintf("exec %s", shellName);
#else
		sys = psprintf("\"%s\"", shellName);
#endif
		result = system(sys);
		free(sys);
	}
	else
		result = system(command);

	if (result == 127 || result == -1)
	{
		pg_log_error("\\!: failed");
		return false;
	}
	return true;
}