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
struct stats {int dummy; } ;
struct saved_value {struct stats stats; } ;
struct runtime_stat {int dummy; } ;
struct perf_stat_output_ctx {scalar_t__ force_header; void* ctx; int /*<<< orphan*/  (* print_metric ) (void*,int /*<<< orphan*/ *,char*,char*,double) ;} ;
struct perf_evsel {char* name; } ;
struct parse_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  (* print_metric_t ) (void*,int /*<<< orphan*/ *,char*,char*,double) ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_NONE ; 
 double avg_stats (struct stats*) ; 
 int /*<<< orphan*/  expr__add_id (struct parse_ctx*,char*,double) ; 
 int /*<<< orphan*/  expr__ctx_init (struct parse_ctx*) ; 
 scalar_t__ expr__parse (double*,struct parse_ctx*,char const**) ; 
 struct saved_value* saved_value_lookup (struct perf_evsel*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct runtime_stat*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 struct stats walltime_nsecs_stats ; 

__attribute__((used)) static void generic_metric(const char *metric_expr,
			   struct perf_evsel **metric_events,
			   char *name,
			   const char *metric_name,
			   double avg,
			   int cpu,
			   struct perf_stat_output_ctx *out,
			   struct runtime_stat *st)
{
	print_metric_t print_metric = out->print_metric;
	struct parse_ctx pctx;
	double ratio;
	int i;
	void *ctxp = out->ctx;

	expr__ctx_init(&pctx);
	expr__add_id(&pctx, name, avg);
	for (i = 0; metric_events[i]; i++) {
		struct saved_value *v;
		struct stats *stats;
		double scale;

		if (!strcmp(metric_events[i]->name, "duration_time")) {
			stats = &walltime_nsecs_stats;
			scale = 1e-9;
		} else {
			v = saved_value_lookup(metric_events[i], cpu, false,
					       STAT_NONE, 0, st);
			if (!v)
				break;
			stats = &v->stats;
			scale = 1.0;
		}
		expr__add_id(&pctx, metric_events[i]->name, avg_stats(stats)*scale);
	}
	if (!metric_events[i]) {
		const char *p = metric_expr;

		if (expr__parse(&ratio, &pctx, &p) == 0)
			print_metric(ctxp, NULL, "%8.1f",
				metric_name ?
				metric_name :
				out->force_header ?  name : "",
				ratio);
		else
			print_metric(ctxp, NULL, NULL,
				     out->force_header ?
				     (metric_name ? metric_name : name) : "", 0);
	} else
		print_metric(ctxp, NULL, NULL, "", 0);
}