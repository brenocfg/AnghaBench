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
struct perf_stat_config {int /*<<< orphan*/  csv_sep; } ;
struct outstate {char* prefix; int nfields; int /*<<< orphan*/  fh; int /*<<< orphan*/  nr; int /*<<< orphan*/  id; int /*<<< orphan*/  evsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  aggr_printout (struct perf_stat_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void new_line_csv(struct perf_stat_config *config, void *ctx)
{
	struct outstate *os = ctx;
	int i;

	fputc('\n', os->fh);
	if (os->prefix)
		fprintf(os->fh, "%s%s", os->prefix, config->csv_sep);
	aggr_printout(config, os->evsel, os->id, os->nr);
	for (i = 0; i < os->nfields; i++)
		fputs(config->csv_sep, os->fh);
}