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
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AssertState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG3 ; 
 char* Dynamic_library_path ; 
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ file_exists (char*) ; 
 int /*<<< orphan*/ * first_dir_separator (char const*) ; 
 char* first_path_var_separator (char const*) ; 
 int /*<<< orphan*/  is_absolute_path (char*) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 char* substitute_libpath_macro (char*) ; 

__attribute__((used)) static char *
find_in_dynamic_libpath(const char *basename)
{
	const char *p;
	size_t		baselen;

	AssertArg(basename != NULL);
	AssertArg(first_dir_separator(basename) == NULL);
	AssertState(Dynamic_library_path != NULL);

	p = Dynamic_library_path;
	if (strlen(p) == 0)
		return NULL;

	baselen = strlen(basename);

	for (;;)
	{
		size_t		len;
		char	   *piece;
		char	   *mangled;
		char	   *full;

		piece = first_path_var_separator(p);
		if (piece == p)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_NAME),
					 errmsg("zero-length component in parameter \"dynamic_library_path\"")));

		if (piece == NULL)
			len = strlen(p);
		else
			len = piece - p;

		piece = palloc(len + 1);
		strlcpy(piece, p, len + 1);

		mangled = substitute_libpath_macro(piece);
		pfree(piece);

		canonicalize_path(mangled);

		/* only absolute paths */
		if (!is_absolute_path(mangled))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_NAME),
					 errmsg("component in parameter \"dynamic_library_path\" is not an absolute path")));

		full = palloc(strlen(mangled) + 1 + baselen + 1);
		sprintf(full, "%s/%s", mangled, basename);
		pfree(mangled);

		elog(DEBUG3, "find_in_dynamic_libpath: trying \"%s\"", full);

		if (file_exists(full))
			return full;

		pfree(full);

		if (p[len] == '\0')
			break;
		else
			p += len + 1;
	}

	return NULL;
}