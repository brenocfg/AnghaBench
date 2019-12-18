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
 char* skip_drive (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

bool
path_contains_parent_reference(const char *path)
{
	int			path_len;

	path = skip_drive(path);	/* C: shouldn't affect our conclusion */

	path_len = strlen(path);

	/*
	 * ".." could be the whole path; otherwise, if it's present it must be at
	 * the beginning, in the middle, or at the end.
	 */
	if (strcmp(path, "..") == 0 ||
		strncmp(path, "../", 3) == 0 ||
		strstr(path, "/../") != NULL ||
		(path_len >= 3 && strcmp(path + path_len - 3, "/..") == 0))
		return true;

	return false;
}