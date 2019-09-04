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
 int /*<<< orphan*/  ODD_COUNTERS ; 
 int /*<<< orphan*/  check_dev_msr () ; 
 int /*<<< orphan*/  check_permissions () ; 
 scalar_t__ do_irtl_snb ; 
 int /*<<< orphan*/  for_all_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_epb ; 
 int /*<<< orphan*/  print_hwp ; 
 int /*<<< orphan*/  print_irtl () ; 
 int /*<<< orphan*/  print_perf_limit ; 
 int /*<<< orphan*/  print_rapl ; 
 int /*<<< orphan*/  print_thermal ; 
 int /*<<< orphan*/  process_cpuid () ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  set_base_cpu () ; 
 int /*<<< orphan*/  set_temperature_target ; 
 int /*<<< orphan*/  setup_all_buffers () ; 

void turbostat_init()
{
	setup_all_buffers();
	set_base_cpu();
	check_dev_msr();
	check_permissions();
	process_cpuid();


	if (!quiet)
		for_all_cpus(print_hwp, ODD_COUNTERS);

	if (!quiet)
		for_all_cpus(print_epb, ODD_COUNTERS);

	if (!quiet)
		for_all_cpus(print_perf_limit, ODD_COUNTERS);

	if (!quiet)
		for_all_cpus(print_rapl, ODD_COUNTERS);

	for_all_cpus(set_temperature_target, ODD_COUNTERS);

	if (!quiet)
		for_all_cpus(print_thermal, ODD_COUNTERS);

	if (!quiet && do_irtl_snb)
		print_irtl();
}