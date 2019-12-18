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
 int MAXPGPATH ; 
 scalar_t__ fsync_fname (char*,int) ; 
 int /*<<< orphan*/  get_parent_directory (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strlen (char*) ; 

int
fsync_parent_path(const char *fname)
{
	char		parentpath[MAXPGPATH];

	strlcpy(parentpath, fname, MAXPGPATH);
	get_parent_directory(parentpath);

	/*
	 * get_parent_directory() returns an empty string if the input argument is
	 * just a file name (see comments in path.c), so handle that as being the
	 * current directory.
	 */
	if (strlen(parentpath) == 0)
		strlcpy(parentpath, ".", MAXPGPATH);

	if (fsync_fname(parentpath, true) != 0)
		return -1;

	return 0;
}