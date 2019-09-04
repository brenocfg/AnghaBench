#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; } ;
struct TYPE_3__ {int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 double NSEC_PER_SEC ; 
 double avg_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int get_precision (double) ; 
 int /*<<< orphan*/  null_run ; 
 scalar_t__ print_free_counters_hint ; 
 scalar_t__ print_mixed_hw_group_error ; 
 int /*<<< orphan*/  print_noise_pct (double,double) ; 
 int /*<<< orphan*/  print_table (int /*<<< orphan*/ *,int,double) ; 
 TYPE_2__ ru_data ; 
 scalar_t__ ru_display ; 
 int run_count ; 
 TYPE_1__ stat_config ; 
 double stddev_stats (int /*<<< orphan*/ *) ; 
 scalar_t__ sysctl__read_int (char*,int*) ; 
 double timeval2double (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walltime_nsecs_stats ; 
 scalar_t__ walltime_run_table ; 

__attribute__((used)) static void print_footer(void)
{
	double avg = avg_stats(&walltime_nsecs_stats) / NSEC_PER_SEC;
	FILE *output = stat_config.output;
	int n;

	if (!null_run)
		fprintf(output, "\n");

	if (run_count == 1) {
		fprintf(output, " %17.9f seconds time elapsed", avg);

		if (ru_display) {
			double ru_utime = timeval2double(&ru_data.ru_utime);
			double ru_stime = timeval2double(&ru_data.ru_stime);

			fprintf(output, "\n\n");
			fprintf(output, " %17.9f seconds user\n", ru_utime);
			fprintf(output, " %17.9f seconds sys\n", ru_stime);
		}
	} else {
		double sd = stddev_stats(&walltime_nsecs_stats) / NSEC_PER_SEC;
		/*
		 * Display at most 2 more significant
		 * digits than the stddev inaccuracy.
		 */
		int precision = get_precision(sd) + 2;

		if (walltime_run_table)
			print_table(output, precision, avg);

		fprintf(output, " %17.*f +- %.*f seconds time elapsed",
			precision, avg, precision, sd);

		print_noise_pct(sd, avg);
	}
	fprintf(output, "\n\n");

	if (print_free_counters_hint &&
	    sysctl__read_int("kernel/nmi_watchdog", &n) >= 0 &&
	    n > 0)
		fprintf(output,
"Some events weren't counted. Try disabling the NMI watchdog:\n"
"	echo 0 > /proc/sys/kernel/nmi_watchdog\n"
"	perf stat ...\n"
"	echo 1 > /proc/sys/kernel/nmi_watchdog\n");

	if (print_mixed_hw_group_error)
		fprintf(output,
			"The events in group usually have to be from "
			"the same PMU. Try reorganizing the group.\n");
}