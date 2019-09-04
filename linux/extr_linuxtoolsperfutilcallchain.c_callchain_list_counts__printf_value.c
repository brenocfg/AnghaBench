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
typedef  int /*<<< orphan*/  u64 ;
struct callchain_list {int /*<<< orphan*/  brtype_stat; int /*<<< orphan*/  from_count; int /*<<< orphan*/  iter_cycles; int /*<<< orphan*/  iter_count; int /*<<< orphan*/  cycles_count; int /*<<< orphan*/  abort_count; int /*<<< orphan*/  predicted_count; int /*<<< orphan*/  branch_count; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int callchain_counts_printf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int callchain_list_counts__printf_value(struct callchain_list *clist,
					FILE *fp, char *bf, int bfsize)
{
	u64 branch_count, predicted_count;
	u64 abort_count, cycles_count;
	u64 iter_count, iter_cycles;
	u64 from_count;

	branch_count = clist->branch_count;
	predicted_count = clist->predicted_count;
	abort_count = clist->abort_count;
	cycles_count = clist->cycles_count;
	iter_count = clist->iter_count;
	iter_cycles = clist->iter_cycles;
	from_count = clist->from_count;

	return callchain_counts_printf(fp, bf, bfsize, branch_count,
				       predicted_count, abort_count,
				       cycles_count, iter_count, iter_cycles,
				       from_count, &clist->brtype_stat);
}