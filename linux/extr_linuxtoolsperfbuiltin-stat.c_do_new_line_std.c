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
struct outstate {int /*<<< orphan*/  fh; int /*<<< orphan*/  nr; int /*<<< orphan*/  id; int /*<<< orphan*/  evsel; int /*<<< orphan*/  prefix; } ;
struct TYPE_2__ {scalar_t__ aggr_mode; } ;

/* Variables and functions */
 scalar_t__ AGGR_NONE ; 
 int /*<<< orphan*/  aggr_printout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static void do_new_line_std(struct outstate *os)
{
	fputc('\n', os->fh);
	fputs(os->prefix, os->fh);
	aggr_printout(os->evsel, os->id, os->nr);
	if (stat_config.aggr_mode == AGGR_NONE)
		fprintf(os->fh, "        ");
	fprintf(os->fh, "                                                 ");
}