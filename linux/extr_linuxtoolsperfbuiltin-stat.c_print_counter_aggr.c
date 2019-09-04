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
struct perf_evsel {double scale; } ;
struct caggr_data {double avg; int /*<<< orphan*/  avg_enabled; int /*<<< orphan*/  avg_running; } ;
struct TYPE_2__ {int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  collect_data (struct perf_evsel*,int /*<<< orphan*/ ,struct caggr_data*) ; 
 int /*<<< orphan*/  counter_aggr_cb ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  metric_only ; 
 int /*<<< orphan*/  printout (int,int /*<<< orphan*/ ,struct perf_evsel*,double,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_stat ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static void print_counter_aggr(struct perf_evsel *counter, char *prefix)
{
	FILE *output = stat_config.output;
	double uval;
	struct caggr_data cd = { .avg = 0.0 };

	if (!collect_data(counter, counter_aggr_cb, &cd))
		return;

	if (prefix && !metric_only)
		fprintf(output, "%s", prefix);

	uval = cd.avg * counter->scale;
	printout(-1, 0, counter, uval, prefix, cd.avg_running, cd.avg_enabled,
		 cd.avg, &rt_stat);
	if (!metric_only)
		fprintf(output, "\n");
}