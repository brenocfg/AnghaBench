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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct thread {int dummy; } ;
struct symbol {int dummy; } ;
struct perf_sample {struct branch_stack* branch_stack; struct ip_callchain* callchain; } ;
struct ip_callchain {scalar_t__* ips; scalar_t__ nr; } ;
struct callchain_cursor {int dummy; } ;
struct branch_stack {int nr; TYPE_1__* entries; } ;
struct branch_flags {int dummy; } ;
struct addr_location {int dummy; } ;
struct TYPE_4__ {scalar_t__ order; } ;
struct TYPE_3__ {scalar_t__ from; scalar_t__ to; struct branch_flags flags; } ;

/* Variables and functions */
 scalar_t__ ORDER_CALLEE ; 
 scalar_t__ PERF_CONTEXT_USER ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 int add_callchain_ip (struct thread*,struct callchain_cursor*,struct symbol**,struct addr_location*,int /*<<< orphan*/ *,scalar_t__,int,struct branch_flags*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__ callchain_param ; 
 int min (int,int) ; 

__attribute__((used)) static int resolve_lbr_callchain_sample(struct thread *thread,
					struct callchain_cursor *cursor,
					struct perf_sample *sample,
					struct symbol **parent,
					struct addr_location *root_al,
					int max_stack)
{
	struct ip_callchain *chain = sample->callchain;
	int chain_nr = min(max_stack, (int)chain->nr), i;
	u8 cpumode = PERF_RECORD_MISC_USER;
	u64 ip, branch_from = 0;

	for (i = 0; i < chain_nr; i++) {
		if (chain->ips[i] == PERF_CONTEXT_USER)
			break;
	}

	/* LBR only affects the user callchain */
	if (i != chain_nr) {
		struct branch_stack *lbr_stack = sample->branch_stack;
		int lbr_nr = lbr_stack->nr, j, k;
		bool branch;
		struct branch_flags *flags;
		/*
		 * LBR callstack can only get user call chain.
		 * The mix_chain_nr is kernel call chain
		 * number plus LBR user call chain number.
		 * i is kernel call chain number,
		 * 1 is PERF_CONTEXT_USER,
		 * lbr_nr + 1 is the user call chain number.
		 * For details, please refer to the comments
		 * in callchain__printf
		 */
		int mix_chain_nr = i + 1 + lbr_nr + 1;

		for (j = 0; j < mix_chain_nr; j++) {
			int err;
			branch = false;
			flags = NULL;

			if (callchain_param.order == ORDER_CALLEE) {
				if (j < i + 1)
					ip = chain->ips[j];
				else if (j > i + 1) {
					k = j - i - 2;
					ip = lbr_stack->entries[k].from;
					branch = true;
					flags = &lbr_stack->entries[k].flags;
				} else {
					ip = lbr_stack->entries[0].to;
					branch = true;
					flags = &lbr_stack->entries[0].flags;
					branch_from =
						lbr_stack->entries[0].from;
				}
			} else {
				if (j < lbr_nr) {
					k = lbr_nr - j - 1;
					ip = lbr_stack->entries[k].from;
					branch = true;
					flags = &lbr_stack->entries[k].flags;
				}
				else if (j > lbr_nr)
					ip = chain->ips[i + 1 - (j - lbr_nr)];
				else {
					ip = lbr_stack->entries[0].to;
					branch = true;
					flags = &lbr_stack->entries[0].flags;
					branch_from =
						lbr_stack->entries[0].from;
				}
			}

			err = add_callchain_ip(thread, cursor, parent,
					       root_al, &cpumode, ip,
					       branch, flags, NULL,
					       branch_from);
			if (err)
				return (err < 0) ? err : 0;
		}
		return 1;
	}

	return 0;
}