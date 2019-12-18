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
 int /*<<< orphan*/  PG_BACKEND_VERSIONSTR ; 
 int /*<<< orphan*/  backend_exec ; 
 scalar_t__ bin_path ; 
 int /*<<< orphan*/  canonicalize_path (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ find_my_exec (char const*,char*) ; 
 int find_other_exec (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_share_path (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  is_absolute_path (scalar_t__) ; 
 char* last_dir_separator (scalar_t__) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  progname ; 
 scalar_t__ share_path ; 
 int /*<<< orphan*/  strcpy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

void
setup_bin_paths(const char *argv0)
{
	int			ret;

	if ((ret = find_other_exec(argv0, "postgres", PG_BACKEND_VERSIONSTR,
							   backend_exec)) < 0)
	{
		char		full_path[MAXPGPATH];

		if (find_my_exec(argv0, full_path) < 0)
			strlcpy(full_path, progname, sizeof(full_path));

		if (ret == -1)
			pg_log_error("The program \"postgres\" is needed by %s but was not found in the\n"
						 "same directory as \"%s\".\n"
						 "Check your installation.",
						 progname, full_path);
		else
			pg_log_error("The program \"postgres\" was found by \"%s\"\n"
						 "but was not the same version as %s.\n"
						 "Check your installation.",
						 full_path, progname);
		exit(1);
	}

	/* store binary directory */
	strcpy(bin_path, backend_exec);
	*last_dir_separator(bin_path) = '\0';
	canonicalize_path(bin_path);

	if (!share_path)
	{
		share_path = pg_malloc(MAXPGPATH);
		get_share_path(backend_exec, share_path);
	}
	else if (!is_absolute_path(share_path))
	{
		pg_log_error("input file location must be an absolute path");
		exit(1);
	}

	canonicalize_path(share_path);
}