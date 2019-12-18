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
struct perf_stat_output_ctx {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* print_metric ) (struct perf_stat_config*,int /*<<< orphan*/ ,char const*,char*,char*,double) ;} ;
struct perf_stat_config {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 char* PERF_COLOR_RED ; 
 int /*<<< orphan*/  STAT_APERF ; 
 int /*<<< orphan*/  STAT_CYCLES ; 
 int /*<<< orphan*/  STAT_SMI_NUM ; 
 int evsel_context (struct evsel*) ; 
 double runtime_stat_avg (struct runtime_stat*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct perf_stat_config*,int /*<<< orphan*/ ,char const*,char*,char*,double) ; 
 int /*<<< orphan*/  stub2 (struct perf_stat_config*,int /*<<< orphan*/ ,char const*,char*,char*,double) ; 

__attribute__((used)) static void print_smi_cost(struct perf_stat_config *config,
			   int cpu, struct evsel *evsel,
			   struct perf_stat_output_ctx *out,
			   struct runtime_stat *st)
{
	double smi_num, aperf, cycles, cost = 0.0;
	int ctx = evsel_context(evsel);
	const char *color = NULL;

	smi_num = runtime_stat_avg(st, STAT_SMI_NUM, ctx, cpu);
	aperf = runtime_stat_avg(st, STAT_APERF, ctx, cpu);
	cycles = runtime_stat_avg(st, STAT_CYCLES, ctx, cpu);

	if ((cycles == 0) || (aperf == 0))
		return;

	if (smi_num)
		cost = (aperf - cycles) / aperf * 100.00;

	if (cost > 10)
		color = PERF_COLOR_RED;
	out->print_metric(config, out->ctx, color, "%8.1f%%", "SMI cycles%", cost);
	out->print_metric(config, out->ctx, NULL, "%4.0f", "SMI#", smi_num);
}