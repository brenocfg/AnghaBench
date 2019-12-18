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
typedef  double u64 ;
struct stats {int dummy; } ;
struct saved_value {double metric_total; scalar_t__ metric_other; struct stats stats; } ;
struct runtime_stat {int dummy; } ;
struct perf_stat_output_ctx {scalar_t__ force_header; void* ctx; int /*<<< orphan*/  (* print_metric ) (struct perf_stat_config*,void*,int /*<<< orphan*/ *,char*,char*,double) ;} ;
struct perf_stat_config {int dummy; } ;
struct parse_ctx {int num_ids; TYPE_1__* ids; } ;
struct evsel {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  (* print_metric_t ) (struct perf_stat_config*,void*,int /*<<< orphan*/ *,char*,char*,double) ;
typedef  int /*<<< orphan*/  metric_bf ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_NONE ; 
 double avg_stats (struct stats*) ; 
 int /*<<< orphan*/  expr__add_id (struct parse_ctx*,char*,double) ; 
 int /*<<< orphan*/  expr__ctx_init (struct parse_ctx*) ; 
 scalar_t__ expr__parse (double*,struct parse_ctx*,char const**) ; 
 scalar_t__ perf_pmu__convert_scale (char const*,char**,double*) ; 
 struct saved_value* saved_value_lookup (struct evsel*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct runtime_stat*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char*,char const*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 struct stats walltime_nsecs_stats ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void generic_metric(struct perf_stat_config *config,
			   const char *metric_expr,
			   struct evsel **metric_events,
			   char *name,
			   const char *metric_name,
			   const char *metric_unit,
			   double avg,
			   int cpu,
			   struct perf_stat_output_ctx *out,
			   struct runtime_stat *st)
{
	print_metric_t print_metric = out->print_metric;
	struct parse_ctx pctx;
	double ratio, scale;
	int i;
	void *ctxp = out->ctx;
	char *n, *pn;

	expr__ctx_init(&pctx);
	/* Must be first id entry */
	expr__add_id(&pctx, name, avg);
	for (i = 0; metric_events[i]; i++) {
		struct saved_value *v;
		struct stats *stats;
		u64 metric_total = 0;

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

			if (v->metric_other)
				metric_total = v->metric_total;
		}

		n = strdup(metric_events[i]->name);
		if (!n)
			return;
		/*
		 * This display code with --no-merge adds [cpu] postfixes.
		 * These are not supported by the parser. Remove everything
		 * after the space.
		 */
		pn = strchr(n, ' ');
		if (pn)
			*pn = 0;

		if (metric_total)
			expr__add_id(&pctx, n, metric_total);
		else
			expr__add_id(&pctx, n, avg_stats(stats)*scale);
	}

	if (!metric_events[i]) {
		const char *p = metric_expr;

		if (expr__parse(&ratio, &pctx, &p) == 0) {
			char *unit;
			char metric_bf[64];

			if (metric_unit && metric_name) {
				if (perf_pmu__convert_scale(metric_unit,
					&unit, &scale) >= 0) {
					ratio *= scale;
				}

				scnprintf(metric_bf, sizeof(metric_bf),
					  "%s  %s", unit, metric_name);
				print_metric(config, ctxp, NULL, "%8.1f",
					     metric_bf, ratio);
			} else {
				print_metric(config, ctxp, NULL, "%8.1f",
					metric_name ?
					metric_name :
					out->force_header ?  name : "",
					ratio);
			}
		} else {
			print_metric(config, ctxp, NULL, NULL,
				     out->force_header ?
				     (metric_name ? metric_name : name) : "", 0);
		}
	} else
		print_metric(config, ctxp, NULL, NULL, "", 0);

	for (i = 1; i < pctx.num_ids; i++)
		zfree(&pctx.ids[i].name);
}