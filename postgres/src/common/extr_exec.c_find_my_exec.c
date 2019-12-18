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
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FILE ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int MAXPGPATH ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  StrNCpy (char*,char const*,int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/ * first_dir_separator (char const*) ; 
 char* first_path_var_separator (char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 char* getenv (char*) ; 
 scalar_t__ is_absolute_path (char const*) ; 
 int /*<<< orphan*/  join_path_components (char*,char*,char const*) ; 
 int /*<<< orphan*/  log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int resolve_symlinks (char*) ; 
 int strlen (char*) ; 
 int validate_exec (char*) ; 

int
find_my_exec(const char *argv0, char *retpath)
{
	char		cwd[MAXPGPATH],
				test_path[MAXPGPATH];
	char	   *path;

	if (!getcwd(cwd, MAXPGPATH))
	{
		log_error(errcode_for_file_access(),
				  _("could not identify current directory: %m"));
		return -1;
	}

	/*
	 * If argv0 contains a separator, then PATH wasn't used.
	 */
	if (first_dir_separator(argv0) != NULL)
	{
		if (is_absolute_path(argv0))
			StrNCpy(retpath, argv0, MAXPGPATH);
		else
			join_path_components(retpath, cwd, argv0);
		canonicalize_path(retpath);

		if (validate_exec(retpath) == 0)
			return resolve_symlinks(retpath);

		log_error(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				  _("invalid binary \"%s\""), retpath);
		return -1;
	}

#ifdef WIN32
	/* Win32 checks the current directory first for names without slashes */
	join_path_components(retpath, cwd, argv0);
	if (validate_exec(retpath) == 0)
		return resolve_symlinks(retpath);
#endif

	/*
	 * Since no explicit path was supplied, the user must have been relying on
	 * PATH.  We'll search the same PATH.
	 */
	if ((path = getenv("PATH")) && *path)
	{
		char	   *startp = NULL,
				   *endp = NULL;

		do
		{
			if (!startp)
				startp = path;
			else
				startp = endp + 1;

			endp = first_path_var_separator(startp);
			if (!endp)
				endp = startp + strlen(startp); /* point to end */

			StrNCpy(test_path, startp, Min(endp - startp + 1, MAXPGPATH));

			if (is_absolute_path(test_path))
				join_path_components(retpath, test_path, argv0);
			else
			{
				join_path_components(retpath, cwd, test_path);
				join_path_components(retpath, retpath, argv0);
			}
			canonicalize_path(retpath);

			switch (validate_exec(retpath))
			{
				case 0:			/* found ok */
					return resolve_symlinks(retpath);
				case -1:		/* wasn't even a candidate, keep looking */
					break;
				case -2:		/* found but disqualified */
					log_error(errcode(ERRCODE_WRONG_OBJECT_TYPE),
							  _("could not read binary \"%s\""),
							  retpath);
					break;
			}
		} while (*endp);
	}

	log_error(errcode(ERRCODE_UNDEFINED_FILE),
			  _("could not find a \"%s\" to execute"), argv0);
	return -1;
}