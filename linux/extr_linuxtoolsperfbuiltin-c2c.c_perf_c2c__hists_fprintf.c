#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_session {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hists; } ;
struct TYPE_4__ {TYPE_1__ hists; scalar_t__ stats_only; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_2__ c2c ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hists__fprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_c2c__display_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_c2c_info (int /*<<< orphan*/ *,struct perf_session*) ; 
 int /*<<< orphan*/  print_pareto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_shared_cacheline_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void perf_c2c__hists_fprintf(FILE *out, struct perf_session *session)
{
	setup_pager();

	print_c2c__display_stats(out);
	fprintf(out, "\n");
	print_shared_cacheline_info(out);
	fprintf(out, "\n");
	print_c2c_info(out, session);

	if (c2c.stats_only)
		return;

	fprintf(out, "\n");
	fprintf(out, "=================================================\n");
	fprintf(out, "           Shared Data Cache Line Table          \n");
	fprintf(out, "=================================================\n");
	fprintf(out, "#\n");

	hists__fprintf(&c2c.hists.hists, true, 0, 0, 0, stdout, true);

	fprintf(out, "\n");
	fprintf(out, "=================================================\n");
	fprintf(out, "      Shared Cache Line Distribution Pareto      \n");
	fprintf(out, "=================================================\n");
	fprintf(out, "#\n");

	print_pareto(out);
}