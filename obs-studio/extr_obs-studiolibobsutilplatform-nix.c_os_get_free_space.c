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
struct statvfs {scalar_t__ f_bfree; scalar_t__ f_bsize; } ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ statvfs (char const*,struct statvfs*) ; 

int64_t os_get_free_space(const char *path)
{
	struct statvfs info;
	int64_t ret = (int64_t)statvfs(path, &info);

	if (ret == 0)
		ret = (int64_t)info.f_bsize * (int64_t)info.f_bfree;

	return ret;
}