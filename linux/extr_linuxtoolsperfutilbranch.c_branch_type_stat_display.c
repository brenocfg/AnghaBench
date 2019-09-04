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
typedef  scalar_t__ u64 ;
struct branch_type_stat {scalar_t__* counts; scalar_t__ cond_fwd; scalar_t__ cond_bwd; scalar_t__ cross_4k; scalar_t__ cross_2m; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PERF_BR_MAX ; 
 char* branch_type_name (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void branch_type_stat_display(FILE *fp, struct branch_type_stat *st)
{
	u64 total = 0;
	int i;

	for (i = 0; i < PERF_BR_MAX; i++)
		total += st->counts[i];

	if (total == 0)
		return;

	fprintf(fp, "\n#");
	fprintf(fp, "\n# Branch Statistics:");
	fprintf(fp, "\n#");

	if (st->cond_fwd > 0) {
		fprintf(fp, "\n%8s: %5.1f%%",
			"COND_FWD",
			100.0 * (double)st->cond_fwd / (double)total);
	}

	if (st->cond_bwd > 0) {
		fprintf(fp, "\n%8s: %5.1f%%",
			"COND_BWD",
			100.0 * (double)st->cond_bwd / (double)total);
	}

	if (st->cross_4k > 0) {
		fprintf(fp, "\n%8s: %5.1f%%",
			"CROSS_4K",
			100.0 * (double)st->cross_4k / (double)total);
	}

	if (st->cross_2m > 0) {
		fprintf(fp, "\n%8s: %5.1f%%",
			"CROSS_2M",
			100.0 * (double)st->cross_2m / (double)total);
	}

	for (i = 0; i < PERF_BR_MAX; i++) {
		if (st->counts[i] > 0)
			fprintf(fp, "\n%8s: %5.1f%%",
				branch_type_name(i),
				100.0 *
				(double)st->counts[i] / (double)total);
	}
}