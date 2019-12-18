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
 size_t PATH_MAX ; 
 int /*<<< orphan*/  p_err (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ validate_tracefs_mnt (char const*,unsigned long) ; 

__attribute__((used)) static bool
find_tracefs_mnt_single(unsigned long magic, char *mnt, const char *mntpt)
{
	size_t src_len;

	if (validate_tracefs_mnt(mntpt, magic))
		return false;

	src_len = strlen(mntpt);
	if (src_len + 1 >= PATH_MAX) {
		p_err("tracefs mount point name too long");
		return false;
	}

	strcpy(mnt, mntpt);
	return true;
}