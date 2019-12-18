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
 int /*<<< orphan*/  GetShortPathName (char*,char*,scalar_t__) ; 
 scalar_t__ MAXPGPATH ; 

void
cleanup_path(char *path)
{
#ifdef WIN32
	char	   *ptr;

	/*
	 * GetShortPathName() will fail if the path does not exist, or short names
	 * are disabled on this file system.  In both cases, we just return the
	 * original path.  This is particularly useful for --sysconfdir, which
	 * might not exist.
	 */
	GetShortPathName(path, path, MAXPGPATH - 1);

	/* Replace '\' with '/' */
	for (ptr = path; *ptr; ptr++)
	{
		if (*ptr == '\\')
			*ptr = '/';
	}
#endif
}