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
struct runtime_stat {int dummy; } ;
struct perf_stat_output_ctx {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* print_metric ) (int /*<<< orphan*/ ,char const*,char*,char*,double) ;} ;
struct perf_evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRC_CACHE_MISSES ; 
 int /*<<< orphan*/  STAT_BRANCHES ; 
 int evsel_context (struct perf_evsel*) ; 
 char* get_ratio_color (int /*<<< orphan*/ ,double) ; 
 double runtime_stat_avg (struct runtime_stat*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,char*,char*,double) ; 

__attribute__((used)) static void print_branch_misses(int cpu,
				struct perf_evsel *evsel,
				double avg,
				struct perf_stat_output_ctx *out,
				struct runtime_stat *st)
{
	double total, ratio = 0.0;
	const char *color;
	int ctx = evsel_context(evsel);

	total = runtime_stat_avg(st, STAT_BRANCHES, ctx, cpu);

	if (total)
		ratio = avg / total * 100.0;

	color = get_ratio_color(GRC_CACHE_MISSES, ratio);

	out->print_metric(out->ctx, color, "%7.2f%%", "of all branches", ratio);
}