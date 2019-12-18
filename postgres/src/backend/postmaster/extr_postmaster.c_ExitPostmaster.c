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
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 
 int /*<<< orphan*/  proc_exit (int) ; 
 scalar_t__ pthread_is_threaded_np () ; 

__attribute__((used)) static void
ExitPostmaster(int status)
{
#ifdef HAVE_PTHREAD_IS_THREADED_NP

	/*
	 * There is no known cause for a postmaster to become multithreaded after
	 * startup.  Recheck to account for the possibility of unknown causes.
	 * This message uses LOG level, because an unclean shutdown at this point
	 * would usually not look much different from a clean shutdown.
	 */
	if (pthread_is_threaded_np() != 0)
		ereport(LOG,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg_internal("postmaster became multithreaded"),
				 errdetail("Please report this to <pgsql-bugs@lists.postgresql.org>.")));
#endif

	/* should cleanup shared memory and kill all backends */

	/*
	 * Not sure of the semantics here.  When the Postmaster dies, should the
	 * backends all be killed? probably not.
	 *
	 * MUST		-- vadim 05-10-1999
	 */

	proc_exit(status);
}