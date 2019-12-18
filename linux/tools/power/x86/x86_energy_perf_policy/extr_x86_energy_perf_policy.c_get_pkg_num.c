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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/ * fopen_or_die (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

unsigned int get_pkg_num(int cpu)
{
	FILE *fp;
	char pathname[128];
	unsigned int pkg;
	int retval;

	sprintf(pathname, "/sys/devices/system/cpu/cpu%d/topology/physical_package_id", cpu);

	fp = fopen_or_die(pathname, "r");
	retval = fscanf(fp, "%d\n", &pkg);
	if (retval != 1)
		errx(1, "%s: failed to parse", pathname);
	return pkg;
}