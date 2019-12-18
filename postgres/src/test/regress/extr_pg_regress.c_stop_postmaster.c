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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPGPATH ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _exit (int) ; 
 char* bindir ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int postmaster_running ; 
 char* progname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int system (char*) ; 
 int /*<<< orphan*/  temp_instance ; 

__attribute__((used)) static void
stop_postmaster(void)
{
	if (postmaster_running)
	{
		/* We use pg_ctl to issue the kill and wait for stop */
		char		buf[MAXPGPATH * 2];
		int			r;

		/* On Windows, system() seems not to force fflush, so... */
		fflush(stdout);
		fflush(stderr);

		snprintf(buf, sizeof(buf),
				 "\"%s%spg_ctl\" stop -D \"%s/data\" -s",
				 bindir ? bindir : "",
				 bindir ? "/" : "",
				 temp_instance);
		r = system(buf);
		if (r != 0)
		{
			fprintf(stderr, _("\n%s: could not stop postmaster: exit code was %d\n"),
					progname, r);
			_exit(2);			/* not exit(), that could be recursive */
		}

		postmaster_running = false;
	}
}