#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct perf_sample {int dummy; } ;
struct branch_stack {int nr; TYPE_3__* entries; } ;
struct addr_map_symbol {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cycles; } ;
struct branch_info {struct addr_map_symbol to; TYPE_1__ flags; int /*<<< orphan*/  from; } ;
struct addr_location {int dummy; } ;
struct TYPE_5__ {scalar_t__ cycles; } ;
struct TYPE_6__ {TYPE_2__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_map_symbol__account_cycles (int /*<<< orphan*/ *,struct addr_map_symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct branch_info*) ; 
 struct branch_info* sample__resolve_bstack (struct perf_sample*,struct addr_location*) ; 

void hist__account_cycles(struct branch_stack *bs, struct addr_location *al,
			  struct perf_sample *sample, bool nonany_branch_mode)
{
	struct branch_info *bi;

	/* If we have branch cycles always annotate them. */
	if (bs && bs->nr && bs->entries[0].flags.cycles) {
		int i;

		bi = sample__resolve_bstack(sample, al);
		if (bi) {
			struct addr_map_symbol *prev = NULL;

			/*
			 * Ignore errors, still want to process the
			 * other entries.
			 *
			 * For non standard branch modes always
			 * force no IPC (prev == NULL)
			 *
			 * Note that perf stores branches reversed from
			 * program order!
			 */
			for (i = bs->nr - 1; i >= 0; i--) {
				addr_map_symbol__account_cycles(&bi[i].from,
					nonany_branch_mode ? NULL : prev,
					bi[i].flags.cycles);
				prev = &bi[i].to;
			}
			free(bi);
		}
	}
}