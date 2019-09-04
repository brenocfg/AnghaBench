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
struct timezone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVEN_COUNTERS ; 
 int /*<<< orphan*/  ODD_COUNTERS ; 
 int /*<<< orphan*/  compute_average (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_is_not_present ; 
 int /*<<< orphan*/  delta_cpu ; 
 int /*<<< orphan*/  do_sleep () ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ exit_requested ; 
 scalar_t__ first_counter_read ; 
 int /*<<< orphan*/  flush_output_stdout () ; 
 int for_all_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ for_all_cpus_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ for_all_proc_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_all_counters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_counters ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,struct timezone*) ; 
 int num_iterations ; 
 int /*<<< orphan*/  re_initialize () ; 
 int /*<<< orphan*/  setup_signal_handler () ; 
 scalar_t__ snapshot_proc_sysfs_files () ; 
 int /*<<< orphan*/  timersub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tv_delta ; 
 int /*<<< orphan*/  tv_even ; 
 int /*<<< orphan*/  tv_odd ; 

void turbostat_loop()
{
	int retval;
	int restarted = 0;
	int done_iters = 0;

	setup_signal_handler();

restart:
	restarted++;

	snapshot_proc_sysfs_files();
	retval = for_all_cpus(get_counters, EVEN_COUNTERS);
	first_counter_read = 0;
	if (retval < -1) {
		exit(retval);
	} else if (retval == -1) {
		if (restarted > 1) {
			exit(retval);
		}
		re_initialize();
		goto restart;
	}
	restarted = 0;
	done_iters = 0;
	gettimeofday(&tv_even, (struct timezone *)NULL);

	while (1) {
		if (for_all_proc_cpus(cpu_is_not_present)) {
			re_initialize();
			goto restart;
		}
		do_sleep();
		if (snapshot_proc_sysfs_files())
			goto restart;
		retval = for_all_cpus(get_counters, ODD_COUNTERS);
		if (retval < -1) {
			exit(retval);
		} else if (retval == -1) {
			re_initialize();
			goto restart;
		}
		gettimeofday(&tv_odd, (struct timezone *)NULL);
		timersub(&tv_odd, &tv_even, &tv_delta);
		if (for_all_cpus_2(delta_cpu, ODD_COUNTERS, EVEN_COUNTERS)) {
			re_initialize();
			goto restart;
		}
		compute_average(EVEN_COUNTERS);
		format_all_counters(EVEN_COUNTERS);
		flush_output_stdout();
		if (exit_requested)
			break;
		if (num_iterations && ++done_iters >= num_iterations)
			break;
		do_sleep();
		if (snapshot_proc_sysfs_files())
			goto restart;
		retval = for_all_cpus(get_counters, EVEN_COUNTERS);
		if (retval < -1) {
			exit(retval);
		} else if (retval == -1) {
			re_initialize();
			goto restart;
		}
		gettimeofday(&tv_even, (struct timezone *)NULL);
		timersub(&tv_even, &tv_odd, &tv_delta);
		if (for_all_cpus_2(delta_cpu, EVEN_COUNTERS, ODD_COUNTERS)) {
			re_initialize();
			goto restart;
		}
		compute_average(ODD_COUNTERS);
		format_all_counters(ODD_COUNTERS);
		flush_output_stdout();
		if (exit_requested)
			break;
		if (num_iterations && ++done_iters >= num_iterations)
			break;
	}
}