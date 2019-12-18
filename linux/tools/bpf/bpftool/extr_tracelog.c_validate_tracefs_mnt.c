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
struct statfs {scalar_t__ f_type; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ statfs (char const*,struct statfs*) ; 

__attribute__((used)) static int validate_tracefs_mnt(const char *mnt, unsigned long magic)
{
	struct statfs st_fs;

	if (statfs(mnt, &st_fs) < 0)
		return -ENOENT;
	if ((unsigned long)st_fs.f_type != magic)
		return -ENOENT;

	return 0;
}