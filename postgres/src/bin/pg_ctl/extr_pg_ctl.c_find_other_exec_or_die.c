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
typedef  int /*<<< orphan*/  full_path ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ find_my_exec (char const*,char*) ; 
 int find_other_exec (char const*,char const*,char const*,char*) ; 
 char* pg_malloc (int) ; 
 char* progname ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  write_stderr (int /*<<< orphan*/ ,char const*,char*,char*) ; 

__attribute__((used)) static char *
find_other_exec_or_die(const char *argv0, const char *target, const char *versionstr)
{
	int			ret;
	char	   *found_path;

	found_path = pg_malloc(MAXPGPATH);

	if ((ret = find_other_exec(argv0, target, versionstr, found_path)) < 0)
	{
		char		full_path[MAXPGPATH];

		if (find_my_exec(argv0, full_path) < 0)
			strlcpy(full_path, progname, sizeof(full_path));

		if (ret == -1)
			write_stderr(_("The program \"%s\" is needed by %s "
						   "but was not found in the\n"
						   "same directory as \"%s\".\n"
						   "Check your installation.\n"),
						 target, progname, full_path);
		else
			write_stderr(_("The program \"%s\" was found by \"%s\"\n"
						   "but was not the same version as %s.\n"
						   "Check your installation.\n"),
						 target, full_path, progname);
		exit(1);
	}

	return found_path;
}