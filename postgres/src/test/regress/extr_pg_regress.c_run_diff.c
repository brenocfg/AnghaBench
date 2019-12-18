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
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ file_size (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int system (char const*) ; 

__attribute__((used)) static int
run_diff(const char *cmd, const char *filename)
{
	int			r;

	r = system(cmd);
	if (!WIFEXITED(r) || WEXITSTATUS(r) > 1)
	{
		fprintf(stderr, _("diff command failed with status %d: %s\n"), r, cmd);
		exit(2);
	}
#ifdef WIN32

	/*
	 * On WIN32, if the 'diff' command cannot be found, system() returns 1,
	 * but produces nothing to stdout, so we check for that here.
	 */
	if (WEXITSTATUS(r) == 1 && file_size(filename) <= 0)
	{
		fprintf(stderr, _("diff command not found: %s\n"), cmd);
		exit(2);
	}
#endif

	return WEXITSTATUS(r);
}