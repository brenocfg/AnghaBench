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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sample_max_stack; int /*<<< orphan*/  exclude_callchain_user; int /*<<< orphan*/  exclude_callchain_kernel; } ;
struct perf_event {TYPE_1__ attr; TYPE_2__* ctx; } ;
struct perf_callchain_entry {int dummy; } ;
struct TYPE_4__ {scalar_t__ task; } ;

/* Variables and functions */
 struct perf_callchain_entry __empty_callchain ; 
 scalar_t__ current ; 
 struct perf_callchain_entry* get_perf_callchain (struct pt_regs*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const,int,int) ; 

struct perf_callchain_entry *
perf_callchain(struct perf_event *event, struct pt_regs *regs)
{
	bool kernel = !event->attr.exclude_callchain_kernel;
	bool user   = !event->attr.exclude_callchain_user;
	/* Disallow cross-task user callchains. */
	bool crosstask = event->ctx->task && event->ctx->task != current;
	const u32 max_stack = event->attr.sample_max_stack;
	struct perf_callchain_entry *callchain;

	if (!kernel && !user)
		return &__empty_callchain;

	callchain = get_perf_callchain(regs, 0, kernel, user,
				       max_stack, crosstask, true);
	return callchain ?: &__empty_callchain;
}