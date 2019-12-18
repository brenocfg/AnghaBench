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
typedef  int uint64_t ;
struct statvfs {scalar_t__ f_bavail; scalar_t__ f_frsize; } ;

/* Variables and functions */
 scalar_t__ statvfs (char const*,struct statvfs*) ; 

uint64_t os_get_free_disk_space(const char *dir)
{
	struct statvfs info;
	if (statvfs(dir, &info) != 0)
		return 0;

	return (uint64_t)info.f_frsize * (uint64_t)info.f_bavail;
}