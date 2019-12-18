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
struct perf_sample {int dummy; } ;
struct branch_stack {int nr; } ;
struct addr_map_symbol {int dummy; } ;
struct branch_info {struct addr_map_symbol to; int /*<<< orphan*/  flags; int /*<<< orphan*/  from; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct branch_info*) ; 
 int /*<<< orphan*/  process_basic_block (struct addr_map_symbol*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct branch_info* sample__resolve_bstack (struct perf_sample*,struct addr_location*) ; 

__attribute__((used)) static void process_branch_stack(struct branch_stack *bs, struct addr_location *al,
				 struct perf_sample *sample)
{
	struct addr_map_symbol *prev = NULL;
	struct branch_info *bi;
	int i;

	if (!bs || !bs->nr)
		return;

	bi = sample__resolve_bstack(sample, al);
	if (!bi)
		return;

	for (i = bs->nr - 1; i >= 0; i--) {
		/*
		 * XXX filter against symbol
		 */
		if (prev)
			process_basic_block(prev, &bi[i].from, &bi[i].flags);
		prev = &bi[i].to;
	}

	free(bi);
}