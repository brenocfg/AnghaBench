#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct thread_stack {int rstate; int cnt; int branch_count; TYPE_2__* stack; int /*<<< orphan*/  kernel_start; TYPE_1__* crp; int /*<<< orphan*/  last_time; int /*<<< orphan*/  cyc_count; int /*<<< orphan*/  insn_count; struct comm* comm; } ;
struct thread {scalar_t__ pid_; scalar_t__ tid; } ;
struct perf_sample {int flags; scalar_t__ ip; scalar_t__ addr; scalar_t__ insn_len; int /*<<< orphan*/  time; scalar_t__ cyc_cnt; scalar_t__ insn_cnt; int /*<<< orphan*/  cpu; } ;
struct comm {int dummy; } ;
struct call_return_processor {int dummy; } ;
struct call_path_root {int dummy; } ;
struct call_path {int dummy; } ;
struct addr_location {scalar_t__ addr; TYPE_3__* sym; } ;
typedef  enum retpoline_state_t { ____Placeholder_retpoline_state_t } retpoline_state_t ;
struct TYPE_7__ {scalar_t__ start; } ;
struct TYPE_6__ {scalar_t__ ret_addr; int non_call; int /*<<< orphan*/  cp; } ;
struct TYPE_5__ {struct call_path_root* cpr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PERF_IP_FLAG_BRANCH ; 
 int PERF_IP_FLAG_CALL ; 
 int PERF_IP_FLAG_INTERRUPT ; 
 int PERF_IP_FLAG_RETURN ; 
 int PERF_IP_FLAG_SYSCALLRET ; 
 int PERF_IP_FLAG_TRACE_BEGIN ; 
 int PERF_IP_FLAG_TRACE_END ; 
 int X86_RETPOLINE_DETECTED ; 
 int X86_RETPOLINE_POSSIBLE ; 
 int __thread_stack__flush (struct thread*,struct thread_stack*) ; 
 struct call_path* call_path__findnew (struct call_path_root*,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct thread_stack* thread__stack (struct thread*,int /*<<< orphan*/ ) ; 
 int thread_stack__bottom (struct thread_stack*,struct perf_sample*,struct addr_location*,struct addr_location*,scalar_t__) ; 
 struct thread_stack* thread_stack__new (struct thread*,int /*<<< orphan*/ ,struct call_return_processor*) ; 
 int thread_stack__no_call_return (struct thread*,struct thread_stack*,struct perf_sample*,struct addr_location*,struct addr_location*,scalar_t__) ; 
 int thread_stack__pop_cp (struct thread*,struct thread_stack*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 int thread_stack__pop_ks (struct thread*,struct thread_stack*,struct perf_sample*,scalar_t__) ; 
 int thread_stack__push_cp (struct thread_stack*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct call_path*,int,int) ; 
 int /*<<< orphan*/  thread_stack__reset (struct thread*,struct thread_stack*) ; 
 int thread_stack__trace_begin (struct thread*,struct thread_stack*,int /*<<< orphan*/ ,scalar_t__) ; 
 int thread_stack__trace_end (struct thread_stack*,struct perf_sample*,scalar_t__) ; 
 int thread_stack__x86_retpoline (struct thread_stack*,struct perf_sample*,struct addr_location*) ; 

int thread_stack__process(struct thread *thread, struct comm *comm,
			  struct perf_sample *sample,
			  struct addr_location *from_al,
			  struct addr_location *to_al, u64 ref,
			  struct call_return_processor *crp)
{
	struct thread_stack *ts = thread__stack(thread, sample->cpu);
	enum retpoline_state_t rstate;
	int err = 0;

	if (ts && !ts->crp) {
		/* Supersede thread_stack__event() */
		thread_stack__reset(thread, ts);
		ts = NULL;
	}

	if (!ts) {
		ts = thread_stack__new(thread, sample->cpu, crp);
		if (!ts)
			return -ENOMEM;
		ts->comm = comm;
	}

	rstate = ts->rstate;
	if (rstate == X86_RETPOLINE_DETECTED)
		ts->rstate = X86_RETPOLINE_POSSIBLE;

	/* Flush stack on exec */
	if (ts->comm != comm && thread->pid_ == thread->tid) {
		err = __thread_stack__flush(thread, ts);
		if (err)
			return err;
		ts->comm = comm;
	}

	/* If the stack is empty, put the current symbol on the stack */
	if (!ts->cnt) {
		err = thread_stack__bottom(ts, sample, from_al, to_al, ref);
		if (err)
			return err;
	}

	ts->branch_count += 1;
	ts->insn_count += sample->insn_cnt;
	ts->cyc_count += sample->cyc_cnt;
	ts->last_time = sample->time;

	if (sample->flags & PERF_IP_FLAG_CALL) {
		bool trace_end = sample->flags & PERF_IP_FLAG_TRACE_END;
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
		err = thread_stack__push_cp(ts, ret_addr, sample->time, ref,
					    cp, false, trace_end);

		/*
		 * A call to the same symbol but not the start of the symbol,
		 * may be the start of a x86 retpoline.
		 */
		if (!err && rstate == X86_RETPOLINE_POSSIBLE && to_al->sym &&
		    from_al->sym == to_al->sym &&
		    to_al->addr != to_al->sym->start)
			ts->rstate = X86_RETPOLINE_DETECTED;

	} else if (sample->flags & PERF_IP_FLAG_RETURN) {
		if (!sample->addr) {
			u32 return_from_kernel = PERF_IP_FLAG_SYSCALLRET |
						 PERF_IP_FLAG_INTERRUPT;

			if (!(sample->flags & return_from_kernel))
				return 0;

			/* Pop kernel stack */
			return thread_stack__pop_ks(thread, ts, sample, ref);
		}

		if (!sample->ip)
			return 0;

		/* x86 retpoline 'return' doesn't match the stack */
		if (rstate == X86_RETPOLINE_DETECTED && ts->cnt > 2 &&
		    ts->stack[ts->cnt - 1].ret_addr != sample->addr)
			return thread_stack__x86_retpoline(ts, sample, to_al);

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
	} else if (sample->flags & PERF_IP_FLAG_BRANCH &&
		   from_al->sym != to_al->sym && to_al->sym &&
		   to_al->addr == to_al->sym->start) {
		struct call_path_root *cpr = ts->crp->cpr;
		struct call_path *cp;

		/*
		 * The compiler might optimize a call/ret combination by making
		 * it a jmp. Make that visible by recording on the stack a
		 * branch to the start of a different symbol. Note, that means
		 * when a ret pops the stack, all jmps must be popped off first.
		 */
		cp = call_path__findnew(cpr, ts->stack[ts->cnt - 1].cp,
					to_al->sym, sample->addr,
					ts->kernel_start);
		err = thread_stack__push_cp(ts, 0, sample->time, ref, cp, false,
					    false);
		if (!err)
			ts->stack[ts->cnt - 1].non_call = true;
	}

	return err;
}