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
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int aggr_mode; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AGGR_CORE 133 
#define  AGGR_GLOBAL 132 
#define  AGGR_NONE 131 
#define  AGGR_SOCKET 130 
#define  AGGR_THREAD 129 
#define  AGGR_UNSET 128 
 int /*<<< orphan*/  CONSOLE_CLEAR ; 
 int /*<<< orphan*/  csv_output ; 
 int /*<<< orphan*/  csv_sep ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ interval_clear ; 
 scalar_t__ metric_only ; 
 int /*<<< orphan*/  print_metric_headers (char*,int) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ stat_config ; 
 char* unit_width ; 

__attribute__((used)) static void print_interval(char *prefix, struct timespec *ts)
{
	FILE *output = stat_config.output;
	static int num_print_interval;

	if (interval_clear)
		puts(CONSOLE_CLEAR);

	sprintf(prefix, "%6lu.%09lu%s", ts->tv_sec, ts->tv_nsec, csv_sep);

	if ((num_print_interval == 0 && !csv_output) || interval_clear) {
		switch (stat_config.aggr_mode) {
		case AGGR_SOCKET:
			fprintf(output, "#           time socket cpus");
			if (!metric_only)
				fprintf(output, "             counts %*s events\n", unit_width, "unit");
			break;
		case AGGR_CORE:
			fprintf(output, "#           time core         cpus");
			if (!metric_only)
				fprintf(output, "             counts %*s events\n", unit_width, "unit");
			break;
		case AGGR_NONE:
			fprintf(output, "#           time CPU    ");
			if (!metric_only)
				fprintf(output, "                counts %*s events\n", unit_width, "unit");
			break;
		case AGGR_THREAD:
			fprintf(output, "#           time             comm-pid");
			if (!metric_only)
				fprintf(output, "                  counts %*s events\n", unit_width, "unit");
			break;
		case AGGR_GLOBAL:
		default:
			fprintf(output, "#           time");
			if (!metric_only)
				fprintf(output, "             counts %*s events\n", unit_width, "unit");
		case AGGR_UNSET:
			break;
		}
	}

	if ((num_print_interval == 0 || interval_clear) && metric_only)
		print_metric_headers(" ", true);
	if (++num_print_interval == 25)
		num_print_interval = 0;
}