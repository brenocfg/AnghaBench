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
struct metric_ctx {int /*<<< orphan*/  fp; int /*<<< orphan*/  evsel; int /*<<< orphan*/  thread; int /*<<< orphan*/  sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char const*,double) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_sample__fprintf_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char const*,double) ; 

__attribute__((used)) static void script_print_metric(void *ctx, const char *color,
			        const char *fmt,
			        const char *unit, double val)
{
	struct metric_ctx *mctx = ctx;

	if (!fmt)
		return;
	perf_sample__fprintf_start(mctx->sample, mctx->thread, mctx->evsel,
				   PERF_RECORD_SAMPLE, mctx->fp);
	fputs("\tmetric: ", mctx->fp);
	if (color)
		color_fprintf(mctx->fp, color, fmt, val);
	else
		printf(fmt, val);
	fprintf(mctx->fp, " %s\n", unit);
}