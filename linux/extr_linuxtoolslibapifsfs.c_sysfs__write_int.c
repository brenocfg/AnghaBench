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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int PATH_MAX ; 
 int filename__write_int (char*,int) ; 
 int snprintf (char*,int,char*,char const*,char const*) ; 
 char* sysfs__mountpoint () ; 

int sysfs__write_int(const char *entry, int value)
{
	char path[PATH_MAX];
	const char *sysfs = sysfs__mountpoint();

	if (!sysfs)
		return -1;

	if (snprintf(path, sizeof(path), "%s/%s", sysfs, entry) >= PATH_MAX)
		return -1;

	return filename__write_int(path, value);
}