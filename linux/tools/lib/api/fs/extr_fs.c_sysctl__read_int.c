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
 int filename__read_int (char*,int*) ; 
 char* procfs__mountpoint () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

int sysctl__read_int(const char *sysctl, int *value)
{
	char path[PATH_MAX];
	const char *procfs = procfs__mountpoint();

	if (!procfs)
		return -1;

	snprintf(path, sizeof(path), "%s/sys/%s", procfs, sysctl);

	return filename__read_int(path, value);
}