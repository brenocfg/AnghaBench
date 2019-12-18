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
struct perf_stat_config {scalar_t__ aggr_mode; } ;
struct outstate {int /*<<< orphan*/  fh; int /*<<< orphan*/  nr; int /*<<< orphan*/  id; int /*<<< orphan*/  evsel; int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 scalar_t__ AGGR_NONE ; 
 int /*<<< orphan*/  aggr_printout (struct perf_stat_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_new_line_std(struct perf_stat_config *config,
			    struct outstate *os)
{
	fputc('\n', os->fh);
	fputs(os->prefix, os->fh);
	aggr_printout(config, os->evsel, os->id, os->nr);
	if (config->aggr_mode == AGGR_NONE)
		fprintf(os->fh, "        ");
	fprintf(os->fh, "                                                 ");
}