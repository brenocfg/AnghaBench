#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct thread {TYPE_1__* ts; } ;
struct TYPE_5__ {scalar_t__ trace_nr; scalar_t__ crp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int PERF_IP_FLAG_CALL ; 
 int PERF_IP_FLAG_RETURN ; 
 int /*<<< orphan*/  __thread_stack__flush (struct thread*,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 TYPE_1__* thread_stack__new (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_stack__pop (TYPE_1__*,scalar_t__) ; 
 int thread_stack__push (TYPE_1__*,scalar_t__) ; 

int thread_stack__event(struct thread *thread, u32 flags, u64 from_ip,
			u64 to_ip, u16 insn_len, u64 trace_nr)
{
	if (!thread)
		return -EINVAL;

	if (!thread->ts) {
		thread->ts = thread_stack__new(thread, NULL);
		if (!thread->ts) {
			pr_warning("Out of memory: no thread stack\n");
			return -ENOMEM;
		}
		thread->ts->trace_nr = trace_nr;
	}

	/*
	 * When the trace is discontinuous, the trace_nr changes.  In that case
	 * the stack might be completely invalid.  Better to report nothing than
	 * to report something misleading, so flush the stack.
	 */
	if (trace_nr != thread->ts->trace_nr) {
		if (thread->ts->trace_nr)
			__thread_stack__flush(thread, thread->ts);
		thread->ts->trace_nr = trace_nr;
	}

	/* Stop here if thread_stack__process() is in use */
	if (thread->ts->crp)
		return 0;

	if (flags & PERF_IP_FLAG_CALL) {
		u64 ret_addr;

		if (!to_ip)
			return 0;
		ret_addr = from_ip + insn_len;
		if (ret_addr == to_ip)
			return 0; /* Zero-length calls are excluded */
		return thread_stack__push(thread->ts, ret_addr);
	} else if (flags & PERF_IP_FLAG_RETURN) {
		if (!from_ip)
			return 0;
		thread_stack__pop(thread->ts, to_ip);
	}

	return 0;
}