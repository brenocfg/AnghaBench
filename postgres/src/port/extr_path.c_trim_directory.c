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
 scalar_t__ IS_DIR_SEP (char) ; 
 char* skip_drive (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
trim_directory(char *path)
{
	char	   *p;

	path = skip_drive(path);

	if (path[0] == '\0')
		return;

	/* back up over trailing slash(es) */
	for (p = path + strlen(path) - 1; IS_DIR_SEP(*p) && p > path; p--)
		;
	/* back up over directory name */
	for (; !IS_DIR_SEP(*p) && p > path; p--)
		;
	/* if multiple slashes before directory name, remove 'em all */
	for (; p > path && IS_DIR_SEP(*(p - 1)); p--)
		;
	/* don't erase a leading slash */
	if (p == path && IS_DIR_SEP(*p))
		p++;
	*p = '\0';
}