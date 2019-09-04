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
struct trace_event_call {int /*<<< orphan*/  prog_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_RUN ; 
 unsigned int BPF_PROG_RUN_ARRAY_CHECK (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_active ; 
 scalar_t__ in_nmi () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ unlikely (int) ; 

unsigned int trace_call_bpf(struct trace_event_call *call, void *ctx)
{
	unsigned int ret;

	if (in_nmi()) /* not supported yet */
		return 1;

	preempt_disable();

	if (unlikely(__this_cpu_inc_return(bpf_prog_active) != 1)) {
		/*
		 * since some bpf program is already running on this cpu,
		 * don't call into another bpf program (same or different)
		 * and don't send kprobe event into ring-buffer,
		 * so return zero here
		 */
		ret = 0;
		goto out;
	}

	/*
	 * Instead of moving rcu_read_lock/rcu_dereference/rcu_read_unlock
	 * to all call sites, we did a bpf_prog_array_valid() there to check
	 * whether call->prog_array is empty or not, which is
	 * a heurisitc to speed up execution.
	 *
	 * If bpf_prog_array_valid() fetched prog_array was
	 * non-NULL, we go into trace_call_bpf() and do the actual
	 * proper rcu_dereference() under RCU lock.
	 * If it turns out that prog_array is NULL then, we bail out.
	 * For the opposite, if the bpf_prog_array_valid() fetched pointer
	 * was NULL, you'll skip the prog_array with the risk of missing
	 * out of events when it was updated in between this and the
	 * rcu_dereference() which is accepted risk.
	 */
	ret = BPF_PROG_RUN_ARRAY_CHECK(call->prog_array, ctx, BPF_PROG_RUN);

 out:
	__this_cpu_dec(bpf_prog_active);
	preempt_enable();

	return ret;
}