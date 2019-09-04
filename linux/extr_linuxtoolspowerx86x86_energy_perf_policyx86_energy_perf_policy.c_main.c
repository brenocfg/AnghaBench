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
 int EINVAL ; 
 int /*<<< orphan*/  cmdline (int,char**) ; 
 scalar_t__ cpu_present_set ; 
 scalar_t__ cpu_selected_set ; 
 int /*<<< orphan*/  cpu_setsize ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  early_cpuid () ; 
 int /*<<< orphan*/  enable_hwp_on_cpu ; 
 int /*<<< orphan*/  for_all_cpus_in_set (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_packages (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ has_hwp_request_pkg ; 
 int /*<<< orphan*/  hwp_update_enabled () ; 
 int /*<<< orphan*/  init_data_structures () ; 
 int /*<<< orphan*/  parse_cpuid () ; 
 scalar_t__ pkg_present_set ; 
 scalar_t__ pkg_selected_set ; 
 int /*<<< orphan*/  print_cpu_msrs ; 
 int /*<<< orphan*/  print_pkg_msrs ; 
 int /*<<< orphan*/  print_version () ; 
 int /*<<< orphan*/  probe_dev_msr () ; 
 scalar_t__ req_update_bounds_check () ; 
 int /*<<< orphan*/  set_base_cpu () ; 
 int /*<<< orphan*/  update_cpu_msrs ; 
 int /*<<< orphan*/  update_epb ; 
 scalar_t__ update_hwp_enable ; 
 int /*<<< orphan*/  update_hwp_request_pkg ; 
 int /*<<< orphan*/  update_sysfs ; 
 int /*<<< orphan*/  update_turbo ; 
 int /*<<< orphan*/  verify_hwp_is_enabled () ; 

int main(int argc, char **argv)
{
	set_base_cpu();
	probe_dev_msr();
	init_data_structures();

	early_cpuid();	/* initial cpuid parse before cmdline */

	cmdline(argc, argv);

	if (debug)
		print_version();

	parse_cpuid();

	 /* If CPU-set and PKG-set are not initialized, default to all CPUs */
	if ((cpu_selected_set == 0) && (pkg_selected_set == 0))
		cpu_selected_set = cpu_present_set;

	/*
	 * If HWP is being enabled, do it now, so that subsequent operations
	 * that access HWP registers can work.
	 */
	if (update_hwp_enable)
		for_all_cpus_in_set(cpu_setsize, cpu_selected_set, enable_hwp_on_cpu);

	/* If HWP present, but disabled, warn and ignore from here forward */
	verify_hwp_is_enabled();

	if (req_update_bounds_check())
		return -EINVAL;

	/* display information only, no updates to settings */
	if (!update_epb && !update_turbo && !hwp_update_enabled()) {
		if (cpu_selected_set)
			for_all_cpus_in_set(cpu_setsize, cpu_selected_set, print_cpu_msrs);

		if (has_hwp_request_pkg) {
			if (pkg_selected_set == 0)
				pkg_selected_set = pkg_present_set;

			for_packages(pkg_selected_set, print_pkg_msrs);
		}

		return 0;
	}

	/* update CPU set */
	if (cpu_selected_set) {
		for_all_cpus_in_set(cpu_setsize, cpu_selected_set, update_sysfs);
		for_all_cpus_in_set(cpu_setsize, cpu_selected_set, update_cpu_msrs);
	} else if (pkg_selected_set)
		for_packages(pkg_selected_set, update_hwp_request_pkg);

	return 0;
}