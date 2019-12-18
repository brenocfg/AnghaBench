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
struct itimerval {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_PROF ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  RAND_cleanup () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getitimer (int /*<<< orphan*/ ,struct itimerval*) ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int write (int,char const*,int /*<<< orphan*/ ) ; 

pid_t
fork_process(void)
{
	pid_t		result;
	const char *oomfilename;

#ifdef LINUX_PROFILE
	struct itimerval prof_itimer;
#endif

	/*
	 * Flush stdio channels just before fork, to avoid double-output problems.
	 * Ideally we'd use fflush(NULL) here, but there are still a few non-ANSI
	 * stdio libraries out there (like SunOS 4.1.x) that coredump if we do.
	 * Presently stdout and stderr are the only stdio output channels used by
	 * the postmaster, so fflush'ing them should be sufficient.
	 */
	fflush(stdout);
	fflush(stderr);

#ifdef LINUX_PROFILE

	/*
	 * Linux's fork() resets the profiling timer in the child process. If we
	 * want to profile child processes then we need to save and restore the
	 * timer setting.  This is a waste of time if not profiling, however, so
	 * only do it if commanded by specific -DLINUX_PROFILE switch.
	 */
	getitimer(ITIMER_PROF, &prof_itimer);
#endif

	result = fork();
	if (result == 0)
	{
		/* fork succeeded, in child */
#ifdef LINUX_PROFILE
		setitimer(ITIMER_PROF, &prof_itimer, NULL);
#endif

		/*
		 * By default, Linux tends to kill the postmaster in out-of-memory
		 * situations, because it blames the postmaster for the sum of child
		 * process sizes *including shared memory*.  (This is unbelievably
		 * stupid, but the kernel hackers seem uninterested in improving it.)
		 * Therefore it's often a good idea to protect the postmaster by
		 * setting its OOM score adjustment negative (which has to be done in
		 * a root-owned startup script).  Since the adjustment is inherited by
		 * child processes, this would ordinarily mean that all the
		 * postmaster's children are equally protected against OOM kill, which
		 * is not such a good idea.  So we provide this code to allow the
		 * children to change their OOM score adjustments again.  Both the
		 * file name to write to and the value to write are controlled by
		 * environment variables, which can be set by the same startup script
		 * that did the original adjustment.
		 */
		oomfilename = getenv("PG_OOM_ADJUST_FILE");

		if (oomfilename != NULL)
		{
			/*
			 * Use open() not stdio, to ensure we control the open flags. Some
			 * Linux security environments reject anything but O_WRONLY.
			 */
			int			fd = open(oomfilename, O_WRONLY, 0);

			/* We ignore all errors */
			if (fd >= 0)
			{
				const char *oomvalue = getenv("PG_OOM_ADJUST_VALUE");
				int			rc;

				if (oomvalue == NULL)	/* supply a useful default */
					oomvalue = "0";

				rc = write(fd, oomvalue, strlen(oomvalue));
				(void) rc;
				close(fd);
			}
		}

		/*
		 * Make sure processes do not share OpenSSL randomness state.
		 */
#ifdef USE_OPENSSL
		RAND_cleanup();
#endif
	}

	return result;
}