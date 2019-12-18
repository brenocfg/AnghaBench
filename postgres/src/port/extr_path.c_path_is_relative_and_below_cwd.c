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
 int /*<<< orphan*/  IS_DIR_SEP (char const) ; 
 scalar_t__ is_absolute_path (char const*) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ path_contains_parent_reference (char const*) ; 

bool
path_is_relative_and_below_cwd(const char *path)
{
	if (is_absolute_path(path))
		return false;
	/* don't allow anything above the cwd */
	else if (path_contains_parent_reference(path))
		return false;
#ifdef WIN32

	/*
	 * On Win32, a drive letter _not_ followed by a slash, e.g. 'E:abc', is
	 * relative to the cwd on that drive, or the drive's root directory if
	 * that drive has no cwd.  Because the path itself cannot tell us which is
	 * the case, we have to assume the worst, i.e. that it is not below the
	 * cwd.  We could use GetFullPathName() to find the full path but that
	 * could change if the current directory for the drive changes underneath
	 * us, so we just disallow it.
	 */
	else if (isalpha((unsigned char) path[0]) && path[1] == ':' &&
			 !IS_DIR_SEP(path[2]))
		return false;
#endif
	else
		return true;
}