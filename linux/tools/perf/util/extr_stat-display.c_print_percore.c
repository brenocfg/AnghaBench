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
struct perf_stat_config {int metric_only; TYPE_1__* aggr_map; scalar_t__ aggr_get_id; int /*<<< orphan*/ * output; } ;
struct evsel {int dummy; } ;
struct TYPE_2__ {int nr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_counter_aggrdata (struct perf_stat_config*,struct evsel*,int,char*,int,int*) ; 

__attribute__((used)) static void print_percore(struct perf_stat_config *config,
			  struct evsel *counter, char *prefix)
{
	bool metric_only = config->metric_only;
	FILE *output = config->output;
	int s;
	bool first = true;

	if (!(config->aggr_map || config->aggr_get_id))
		return;

	for (s = 0; s < config->aggr_map->nr; s++) {
		if (prefix && metric_only)
			fprintf(output, "%s", prefix);

		print_counter_aggrdata(config, counter, s,
				       prefix, metric_only,
				       &first);
	}

	if (metric_only)
		fputc('\n', output);
}