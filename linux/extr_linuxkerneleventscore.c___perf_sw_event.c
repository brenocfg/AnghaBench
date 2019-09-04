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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ___perf_sw_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int perf_swevent_get_recursion_context () ; 
 int /*<<< orphan*/  perf_swevent_put_recursion_context (int) ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 scalar_t__ unlikely (int) ; 

void __perf_sw_event(u32 event_id, u64 nr, struct pt_regs *regs, u64 addr)
{
	int rctx;

	preempt_disable_notrace();
	rctx = perf_swevent_get_recursion_context();
	if (unlikely(rctx < 0))
		goto fail;

	___perf_sw_event(event_id, nr, regs, addr);

	perf_swevent_put_recursion_context(rctx);
fail:
	preempt_enable_notrace();
}