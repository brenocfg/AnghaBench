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
union perf_event {int /*<<< orphan*/  stat_config; } ;
struct perf_stat_config {int aggr_mode; int scale; int interval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  perf_event__read_stat_config (struct perf_stat_config*,int /*<<< orphan*/ *) ; 

size_t perf_event__fprintf_stat_config(union perf_event *event, FILE *fp)
{
	struct perf_stat_config sc;
	size_t ret;

	perf_event__read_stat_config(&sc, &event->stat_config);

	ret  = fprintf(fp, "\n");
	ret += fprintf(fp, "... aggr_mode %d\n", sc.aggr_mode);
	ret += fprintf(fp, "... scale     %d\n", sc.scale);
	ret += fprintf(fp, "... interval  %u\n", sc.interval);

	return ret;
}