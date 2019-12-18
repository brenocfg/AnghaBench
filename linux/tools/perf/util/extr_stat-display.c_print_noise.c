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
struct perf_stat_evsel {int /*<<< orphan*/ * res_stats; } ;
struct perf_stat_config {int run_count; } ;
struct evsel {struct perf_stat_evsel* stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_noise_pct (struct perf_stat_config*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  stddev_stats (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_noise(struct perf_stat_config *config,
			struct evsel *evsel, double avg)
{
	struct perf_stat_evsel *ps;

	if (config->run_count == 1)
		return;

	ps = evsel->stats;
	print_noise_pct(config, stddev_stats(&ps->res_stats[0]), avg);
}