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
typedef  scalar_t__ u64 ;
struct thread_stack {int cnt; int branch_count; int /*<<< orphan*/  kernel_start; TYPE_2__* stack; TYPE_1__* crp; int /*<<< orphan*/  last_time; struct comm* comm; } ;
struct thread {scalar_t__ pid_; scalar_t__ tid; struct thread_stack* ts; } ;
struct perf_sample {int flags; int /*<<< orphan*/  time; scalar_t__ addr; scalar_t__ ip; scalar_t__ insn_len; } ;
struct comm {int dummy; } ;
struct call_return_processor {int dummy; } ;
struct call_path_root {int dummy; } ;
struct call_path {int dummy; } ;
struct addr_location {int /*<<< orphan*/  sym; } ;
struct TYPE_4__ {int /*<<< orphan*/  cp; } ;
struct TYPE_3__ {struct call_path_root* cpr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PERF_IP_FLAG_CALL ; 
 int PERF_IP_FLAG_RETURN ; 
 int PERF_IP_FLAG_TRACE_BEGIN ; 
 int PERF_IP_FLAG_TRACE_END ; 
 int __thread_stack__flush (struct thread*,struct thread_stack*) ; 
 struct call_path* call_path__findnew (struct call_path_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int thread_stack__bottom (struct thread*,struct thread_stack*,struct perf_sample*,struct addr_location*,struct addr_location*,scalar_t__) ; 
 int /*<<< orphan*/  thread_stack__free (struct thread*) ; 
 void* thread_stack__new (struct thread*,struct call_return_processor*) ; 
 int thread_stack__no_call_return (struct thread*,struct thread_stack*,struct perf_sample*,struct addr_location*,struct addr_location*,scalar_t__) ; 
 int thread_stack__pop_cp (struct thread*,struct thread_stack*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int thread_stack__push_cp (struct thread_stack*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct call_path*,int) ; 
 int thread_stack__trace_begin (struct thread*,struct thread_stack*,int /*<<< orphan*/ ,scalar_t__) ; 
 int thread_stack__trace_end (struct thread_stack*,struct perf_sample*,scalar_t__) ; 

int thread_stack__process(struct thread *thread, struct comm *comm,
			  struct perf_sample *sample,
			  struct addr_location *from_al,
			  struct addr_location *to_al, u64 ref,
			  struct call_return_processor *crp)
{
	struct thread_stack *ts = thread->ts;
	int err = 0;

	if (ts) {
		if (!ts->crp) {
			/* Supersede thread_stack__event() */
			thread_stack__free(thread);
			thread->ts = thread_stack__new(thread, crp);
			if (!thread->ts)
				return -ENOMEM;
			ts = thread->ts;
			ts->comm = comm;
		}
	} else {
		thread->ts = thread_stack__new(thread, crp);
		if (!thread->ts)
			return -ENOMEM;
		ts = thread->ts;
		ts->comm = comm;
	}

	/* Flush stack on exec */
	if (ts->comm != comm && thread->pid_ == thread->tid) {
		err = __thread_stack__flush(thread, ts);
		if (err)
			return err;
		ts->comm = comm;
	}

	/* If the stack is empty, put the current symbol on the stack */
	if (!ts->cnt) {
		err = thread_stack__bottom(thread, ts, sample, from_al, to_al,
					   ref);
		if (err)
			return err;
	}

	ts->branch_count += 1;
	ts->last_time = sample->time;

	if (sample->flags & PERF_IP_FLAG_CALL) {
		struct call_path_root *cpr = ts->crp->cpr;
		struct call_path *cp;
		u64 ret_addr;

		if (!sample->ip || !sample->addr)
			return 0;

		ret_addr = sample->ip + sample->insn_len;
		if (ret_addr == sample->addr)
			return 0; /* Zero-length calls are excluded */

		cp = call_path__findnew(cpr, ts->stack[ts->cnt - 1].cp,
					to_al->sym, sample->addr,
					ts->kernel_start);
		if (!cp)
			return -ENOMEM;
		err = thread_stack__push_cp(ts, ret_addr, sample->time, ref,
					    cp, false);
	} else if (sample->flags & PERF_IP_FLAG_RETURN) {
		if (!sample->ip || !sample->addr)
			return 0;

		err = thread_stack__pop_cp(thread, ts, sample->addr,
					   sample->time, ref, from_al->sym);
		if (err) {
			if (err < 0)
				return err;
			err = thread_stack__no_call_return(thread, ts, sample,
							   from_al, to_al, ref);
		}
	} else if (sample->flags & PERF_IP_FLAG_TRACE_BEGIN) {
		err = thread_stack__trace_begin(thread, ts, sample->time, ref);
	} else if (sample->flags & PERF_IP_FLAG_TRACE_END) {
		err = thread_stack__trace_end(ts, sample, ref);
	}

	return err;
}