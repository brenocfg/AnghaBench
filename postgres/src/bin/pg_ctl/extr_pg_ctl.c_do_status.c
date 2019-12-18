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
typedef  int /*<<< orphan*/  pid_t ;
typedef  scalar_t__ pgpid_t ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free_readfile (char**) ; 
 scalar_t__ get_pgpid (int) ; 
 scalar_t__ postmaster_is_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postopts_file ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  puts (char*) ; 
 char** readfile (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
do_status(void)
{
	pgpid_t		pid;

	pid = get_pgpid(true);
	/* Is there a pid file? */
	if (pid != 0)
	{
		/* standalone backend? */
		if (pid < 0)
		{
			pid = -pid;
			if (postmaster_is_alive((pid_t) pid))
			{
				printf(_("%s: single-user server is running (PID: %ld)\n"),
					   progname, pid);
				return;
			}
		}
		else
			/* must be a postmaster */
		{
			if (postmaster_is_alive((pid_t) pid))
			{
				char	  **optlines;
				char	  **curr_line;
				int			numlines;

				printf(_("%s: server is running (PID: %ld)\n"),
					   progname, pid);

				optlines = readfile(postopts_file, &numlines);
				if (optlines != NULL)
				{
					for (curr_line = optlines; *curr_line != NULL; curr_line++)
						puts(*curr_line);

					/* Free the results of readfile */
					free_readfile(optlines);
				}
				return;
			}
		}
	}
	printf(_("%s: no server running\n"), progname);

	/*
	 * The Linux Standard Base Core Specification 3.1 says this should return
	 * '3, program is not running'
	 * https://refspecs.linuxbase.org/LSB_3.1.0/LSB-Core-generic/LSB-Core-generic/iniscrptact.html
	 */
	exit(3);
}