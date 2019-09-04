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

/* Variables and functions */
 int PERF_BR_COND ; 
 int PERF_BR_MAX ; 
 char* branch_type_name (int) ; 
 scalar_t__ count_str_scnprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

int branch_type_str(struct branch_type_stat *st, char *bf, int size)
{
	int i, j = 0, printed = 0;
	u64 total = 0;

	for (i = 0; i < PERF_BR_MAX; i++)
		total += st->counts[i];

	if (total == 0)
		return 0;

	if (st->cond_fwd > 0)
		printed += count_str_scnprintf(j++, "COND_FWD", bf + printed, size - printed);

	if (st->cond_bwd > 0)
		printed += count_str_scnprintf(j++, "COND_BWD", bf + printed, size - printed);

	for (i = 0; i < PERF_BR_MAX; i++) {
		if (i == PERF_BR_COND)
			continue;

		if (st->counts[i] > 0)
			printed += count_str_scnprintf(j++, branch_type_name(i), bf + printed, size - printed);
	}

	if (st->cross_4k > 0)
		printed += count_str_scnprintf(j++, "CROSS_4K", bf + printed, size - printed);

	if (st->cross_2m > 0)
		printed += count_str_scnprintf(j++, "CROSS_2M", bf + printed, size - printed);

	return printed;
}