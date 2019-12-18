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
 scalar_t__ debug ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int ratio_2_sysfs_khz (unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 

void update_cpufreq_scaling_freq(int is_max, int cpu, unsigned int ratio)
{
	char pathname[64];
	FILE *fp;
	int retval;
	int khz;

	sprintf(pathname, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_%s_freq",
		cpu, is_max ? "max" : "min");

	fp = fopen(pathname, "w");
	if (!fp) {
		if (debug)
			perror(pathname);
		return;
	}

	khz = ratio_2_sysfs_khz(ratio);
	retval = fprintf(fp, "%d", khz);
	if (retval < 0)
		if (debug)
			perror("fprintf");
	if (debug)
		printf("echo %d > %s\n", khz, pathname);

	fclose(fp);
}