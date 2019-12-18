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
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 char* _ (char*) ; 
 char* pg_strsignal (int) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

char *
wait_result_to_str(int exitstatus)
{
	char		str[512];

	if (WIFEXITED(exitstatus))
	{
		/*
		 * Give more specific error message for some common exit codes that
		 * have a special meaning in shells.
		 */
		switch (WEXITSTATUS(exitstatus))
		{
			case 126:
				snprintf(str, sizeof(str), _("command not executable"));
				break;

			case 127:
				snprintf(str, sizeof(str), _("command not found"));
				break;

			default:
				snprintf(str, sizeof(str),
						 _("child process exited with exit code %d"),
						 WEXITSTATUS(exitstatus));
		}
	}
	else if (WIFSIGNALED(exitstatus))
	{
#if defined(WIN32)
		snprintf(str, sizeof(str),
				 _("child process was terminated by exception 0x%X"),
				 WTERMSIG(exitstatus));
#else
		snprintf(str, sizeof(str),
				 _("child process was terminated by signal %d: %s"),
				 WTERMSIG(exitstatus), pg_strsignal(WTERMSIG(exitstatus)));
#endif
	}
	else
		snprintf(str, sizeof(str),
				 _("child process exited with unrecognized status %d"),
				 exitstatus);

	return pstrdup(str);
}