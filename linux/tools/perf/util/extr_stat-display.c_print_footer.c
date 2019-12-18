#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; } ;
struct perf_stat_config {int run_count; scalar_t__ print_mixed_hw_group_error; scalar_t__ print_free_counters_hint; scalar_t__ walltime_run_table; int /*<<< orphan*/  walltime_nsecs_stats; TYPE_1__ ru_data; scalar_t__ ru_display; int /*<<< orphan*/  null_run; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 double NSEC_PER_SEC ; 
 double avg_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int get_precision (double) ; 
 int /*<<< orphan*/  print_noise_pct (struct perf_stat_config*,double,double) ; 
 int /*<<< orphan*/  print_table (struct perf_stat_config*,int /*<<< orphan*/ *,int,double) ; 
 double stddev_stats (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl__read_int (char*,int*) ; 
 double timeval2double (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_footer(struct perf_stat_config *config)
{
	double avg = avg_stats(config->walltime_nsecs_stats) / NSEC_PER_SEC;
	FILE *output = config->output;
	int n;

	if (!config->null_run)
		fprintf(output, "\n");

	if (config->run_count == 1) {
		fprintf(output, " %17.9f seconds time elapsed", avg);

		if (config->ru_display) {
			double ru_utime = timeval2double(&config->ru_data.ru_utime);
			double ru_stime = timeval2double(&config->ru_data.ru_stime);

			fprintf(output, "\n\n");
			fprintf(output, " %17.9f seconds user\n", ru_utime);
			fprintf(output, " %17.9f seconds sys\n", ru_stime);
		}
	} else {
		double sd = stddev_stats(config->walltime_nsecs_stats) / NSEC_PER_SEC;
		/*
		 * Display at most 2 more significant
		 * digits than the stddev inaccuracy.
		 */
		int precision = get_precision(sd) + 2;

		if (config->walltime_run_table)
			print_table(config, output, precision, avg);

		fprintf(output, " %17.*f +- %.*f seconds time elapsed",
			precision, avg, precision, sd);

		print_noise_pct(config, sd, avg);
	}
	fprintf(output, "\n\n");

	if (config->print_free_counters_hint &&
	    sysctl__read_int("kernel/nmi_watchdog", &n) >= 0 &&
	    n > 0)
		fprintf(output,
"Some events weren't counted. Try disabling the NMI watchdog:\n"
"	echo 0 > /proc/sys/kernel/nmi_watchdog\n"
"	perf stat ...\n"
"	echo 1 > /proc/sys/kernel/nmi_watchdog\n");

	if (config->print_mixed_hw_group_error)
		fprintf(output,
			"The events in group usually have to be from "
			"the same PMU. Try reorganizing the group.\n");
}