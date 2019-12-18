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
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 char* first_dir_separator (char const*) ; 
 int /*<<< orphan*/  pkglib_path ; 
 char* psprintf (char*,int /*<<< orphan*/ ,char const*) ; 
 char* pstrdup (char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static char *
substitute_libpath_macro(const char *name)
{
	const char *sep_ptr;

	AssertArg(name != NULL);

	/* Currently, we only recognize $libdir at the start of the string */
	if (name[0] != '$')
		return pstrdup(name);

	if ((sep_ptr = first_dir_separator(name)) == NULL)
		sep_ptr = name + strlen(name);

	if (strlen("$libdir") != sep_ptr - name ||
		strncmp(name, "$libdir", strlen("$libdir")) != 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_NAME),
				 errmsg("invalid macro name in dynamic library path: %s",
						name)));

	return psprintf("%s%s", pkglib_path, sep_ptr);
}