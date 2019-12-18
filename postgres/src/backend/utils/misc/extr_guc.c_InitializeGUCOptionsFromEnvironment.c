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
 long Min (long,int) ; 
 int /*<<< orphan*/  PGC_POSTMASTER ; 
 int /*<<< orphan*/  PGC_S_ENV_VAR ; 
 long STACK_DEPTH_SLOP ; 
 int /*<<< orphan*/  SetConfigOption (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long get_stack_depth_rlimit () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 

__attribute__((used)) static void
InitializeGUCOptionsFromEnvironment(void)
{
	char	   *env;
	long		stack_rlimit;

	env = getenv("PGPORT");
	if (env != NULL)
		SetConfigOption("port", env, PGC_POSTMASTER, PGC_S_ENV_VAR);

	env = getenv("PGDATESTYLE");
	if (env != NULL)
		SetConfigOption("datestyle", env, PGC_POSTMASTER, PGC_S_ENV_VAR);

	env = getenv("PGCLIENTENCODING");
	if (env != NULL)
		SetConfigOption("client_encoding", env, PGC_POSTMASTER, PGC_S_ENV_VAR);

	/*
	 * rlimit isn't exactly an "environment variable", but it behaves about
	 * the same.  If we can identify the platform stack depth rlimit, increase
	 * default stack depth setting up to whatever is safe (but at most 2MB).
	 */
	stack_rlimit = get_stack_depth_rlimit();
	if (stack_rlimit > 0)
	{
		long		new_limit = (stack_rlimit - STACK_DEPTH_SLOP) / 1024L;

		if (new_limit > 100)
		{
			char		limbuf[16];

			new_limit = Min(new_limit, 2048);
			sprintf(limbuf, "%ld", new_limit);
			SetConfigOption("max_stack_depth", limbuf,
							PGC_POSTMASTER, PGC_S_ENV_VAR);
		}
	}
}