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

/* Variables and functions */
 scalar_t__ cmd_help ; 
 scalar_t__ cpufreq_sysfs_present () ; 
 int /*<<< orphan*/  enable_clos_qos_config ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_online_package_in_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  for_each_online_target_cpu_in_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isst_ctdp_display_information_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isst_ctdp_display_information_start (int /*<<< orphan*/ ) ; 
 scalar_t__ max_target_cpus ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void set_clos_enable(void)
{
	int status = 1;

	if (cmd_help) {
		fprintf(stderr, "Enable core-power for a package/die\n");
		fprintf(stderr,
			"\tClos Enable: Specify priority type with [--priority|-p]\n");
		fprintf(stderr, "\t\t 0: Proportional, 1: Ordered\n");
		exit(0);
	}

	if (cpufreq_sysfs_present()) {
		fprintf(stderr,
			"cpufreq subsystem and core-power enable will interfere with each other!\n");
	}

	isst_ctdp_display_information_start(outf);
	if (max_target_cpus)
		for_each_online_target_cpu_in_set(enable_clos_qos_config, NULL,
						  NULL, NULL, &status);
	else
		for_each_online_package_in_set(enable_clos_qos_config, NULL,
					       NULL, NULL, &status);
	isst_ctdp_display_information_end(outf);
}