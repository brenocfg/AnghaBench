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
 int /*<<< orphan*/  AssertArg (char const*) ; 
 int /*<<< orphan*/  DLSUFFIX ; 
 scalar_t__ file_exists (char*) ; 
 char* find_in_dynamic_libpath (char const*) ; 
 int /*<<< orphan*/ * first_dir_separator (char const*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* psprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 char* pstrdup (char const*) ; 
 char* substitute_libpath_macro (char const*) ; 

__attribute__((used)) static char *
expand_dynamic_library_name(const char *name)
{
	bool		have_slash;
	char	   *new;
	char	   *full;

	AssertArg(name);

	have_slash = (first_dir_separator(name) != NULL);

	if (!have_slash)
	{
		full = find_in_dynamic_libpath(name);
		if (full)
			return full;
	}
	else
	{
		full = substitute_libpath_macro(name);
		if (file_exists(full))
			return full;
		pfree(full);
	}

	new = psprintf("%s%s", name, DLSUFFIX);

	if (!have_slash)
	{
		full = find_in_dynamic_libpath(new);
		pfree(new);
		if (full)
			return full;
	}
	else
	{
		full = substitute_libpath_macro(new);
		pfree(new);
		if (file_exists(full))
			return full;
		pfree(full);
	}

	/*
	 * If we can't find the file, just return the string as-is. The ensuing
	 * load attempt will fail and report a suitable message.
	 */
	return pstrdup(name);
}