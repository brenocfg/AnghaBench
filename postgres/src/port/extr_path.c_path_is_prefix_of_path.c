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
 scalar_t__ IS_DIR_SEP (char const) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

bool
path_is_prefix_of_path(const char *path1, const char *path2)
{
	int			path1_len = strlen(path1);

	if (strncmp(path1, path2, path1_len) == 0 &&
		(IS_DIR_SEP(path2[path1_len]) || path2[path1_len] == '\0'))
		return true;
	return false;
}