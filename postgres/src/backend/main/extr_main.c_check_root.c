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
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 scalar_t__ pgwin32_is_admin () ; 
 int /*<<< orphan*/  write_stderr (char*,...) ; 

__attribute__((used)) static void
check_root(const char *progname)
{
#ifndef WIN32
	if (geteuid() == 0)
	{
		write_stderr("\"root\" execution of the PostgreSQL server is not permitted.\n"
					 "The server must be started under an unprivileged user ID to prevent\n"
					 "possible system security compromise.  See the documentation for\n"
					 "more information on how to properly start the server.\n");
		exit(1);
	}

	/*
	 * Also make sure that real and effective uids are the same. Executing as
	 * a setuid program from a root shell is a security hole, since on many
	 * platforms a nefarious subroutine could setuid back to root if real uid
	 * is root.  (Since nobody actually uses postgres as a setuid program,
	 * trying to actively fix this situation seems more trouble than it's
	 * worth; we'll just expend the effort to check for it.)
	 */
	if (getuid() != geteuid())
	{
		write_stderr("%s: real and effective user IDs must match\n",
					 progname);
		exit(1);
	}
#else							/* WIN32 */
	if (pgwin32_is_admin())
	{
		write_stderr("Execution of PostgreSQL by a user with administrative permissions is not\n"
					 "permitted.\n"
					 "The server must be started under an unprivileged user ID to prevent\n"
					 "possible system security compromises.  See the documentation for\n"
					 "more information on how to properly start the server.\n");
		exit(1);
	}
#endif							/* WIN32 */
}