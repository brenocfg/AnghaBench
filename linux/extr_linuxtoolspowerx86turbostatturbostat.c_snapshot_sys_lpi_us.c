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
 int /*<<< orphan*/  cpuidle_cur_sys_lpi_us ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_die (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

int snapshot_sys_lpi_us(void)
{
	FILE *fp;
	int retval;

	fp = fopen_or_die("/sys/devices/system/cpu/cpuidle/low_power_idle_system_residency_us", "r");

	retval = fscanf(fp, "%lld", &cpuidle_cur_sys_lpi_us);
	if (retval != 1)
		err(1, "SYS LPI");

	fclose(fp);

	return 0;
}