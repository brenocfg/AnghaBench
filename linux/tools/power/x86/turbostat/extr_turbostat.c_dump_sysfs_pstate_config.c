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
typedef  int /*<<< orphan*/  governor_buf ;
typedef  int /*<<< orphan*/  driver_buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int base_cpu ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void
dump_sysfs_pstate_config(void)
{
	char path[64];
	char driver_buf[64];
	char governor_buf[64];
	FILE *input;
	int turbo;

	sprintf(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_driver",
			base_cpu);
	input = fopen(path, "r");
	if (input == NULL) {
		fprintf(outf, "NSFOD %s\n", path);
		return;
	}
	if (!fgets(driver_buf, sizeof(driver_buf), input))
		err(1, "%s: failed to read file", path);
	fclose(input);

	sprintf(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_governor",
			base_cpu);
	input = fopen(path, "r");
	if (input == NULL) {
		fprintf(outf, "NSFOD %s\n", path);
		return;
	}
	if (!fgets(governor_buf, sizeof(governor_buf), input))
		err(1, "%s: failed to read file", path);
	fclose(input);

	fprintf(outf, "cpu%d: cpufreq driver: %s", base_cpu, driver_buf);
	fprintf(outf, "cpu%d: cpufreq governor: %s", base_cpu, governor_buf);

	sprintf(path, "/sys/devices/system/cpu/cpufreq/boost");
	input = fopen(path, "r");
	if (input != NULL) {
		if (fscanf(input, "%d", &turbo) != 1)
			err(1, "%s: failed to parse number from file", path);
		fprintf(outf, "cpufreq boost: %d\n", turbo);
		fclose(input);
	}

	sprintf(path, "/sys/devices/system/cpu/intel_pstate/no_turbo");
	input = fopen(path, "r");
	if (input != NULL) {
		if (fscanf(input, "%d", &turbo) != 1)
			err(1, "%s: failed to parse number from file", path);
		fprintf(outf, "cpufreq intel_pstate no_turbo: %d\n", turbo);
		fclose(input);
	}
}