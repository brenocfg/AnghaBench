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
 int MAX_SYSFS_PATH ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

int open_sysfs(const char *sys_pfx, const char *node, int flags)
{
	int fd;
	char path[MAX_SYSFS_PATH];

	snprintf(path, sizeof(path), "%s%s", sys_pfx, node);
	fd = open(path, flags);
	if (fd < 0) {
		fprintf(stderr, "unable to open %s\n", path);
		abort();
	}
	return fd;
}