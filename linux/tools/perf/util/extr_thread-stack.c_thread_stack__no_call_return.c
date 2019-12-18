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
struct thread_stack {scalar_t__ kernel_start; int cnt; TYPE_2__* stack; TYPE_1__* crp; } ;
struct thread {int dummy; } ;
struct symbol {int dummy; } ;
struct perf_sample {scalar_t__ addr; scalar_t__ time; scalar_t__ ip; } ;
struct call_path {struct symbol* sym; } ;
struct call_path_root {struct call_path call_path; } ;
struct addr_location {struct symbol* sym; } ;
struct TYPE_4__ {int non_call; struct call_path* cp; } ;
struct TYPE_3__ {struct call_path_root* cpr; } ;

/* Variables and functions */
 struct call_path* call_path__findnew (struct call_path_root*,struct call_path*,struct symbol*,scalar_t__,scalar_t__) ; 
 int thread_stack__call_return (struct thread*,struct thread_stack*,int,scalar_t__,scalar_t__,int) ; 
 scalar_t__ thread_stack__in_kernel (struct thread_stack*) ; 
 int thread_stack__pop_ks (struct thread*,struct thread_stack*,struct perf_sample*,scalar_t__) ; 
 int thread_stack__push_cp (struct thread_stack*,scalar_t__,scalar_t__,scalar_t__,struct call_path*,int,int) ; 

__attribute__((used)) static int thread_stack__no_call_return(struct thread *thread,
					struct thread_stack *ts,
					struct perf_sample *sample,
					struct addr_location *from_al,
					struct addr_location *to_al, u64 ref)
{
	struct call_path_root *cpr = ts->crp->cpr;
	struct call_path *root = &cpr->call_path;
	struct symbol *fsym = from_al->sym;
	struct symbol *tsym = to_al->sym;
	struct call_path *cp, *parent;
	u64 ks = ts->kernel_start;
	u64 addr = sample->addr;
	u64 tm = sample->time;
	u64 ip = sample->ip;
	int err;

	if (ip >= ks && addr < ks) {
		/* Return to userspace, so pop all kernel addresses */
		err = thread_stack__pop_ks(thread, ts, sample, ref);
		if (err)
			return err;

		/* If the stack is empty, push the userspace address */
		if (!ts->cnt) {
			cp = call_path__findnew(cpr, root, tsym, addr, ks);
			return thread_stack__push_cp(ts, 0, tm, ref, cp, true,
						     false);
		}
	} else if (thread_stack__in_kernel(ts) && ip < ks) {
		/* Return to userspace, so pop all kernel addresses */
		err = thread_stack__pop_ks(thread, ts, sample, ref);
		if (err)
			return err;
	}

	if (ts->cnt)
		parent = ts->stack[ts->cnt - 1].cp;
	else
		parent = root;

	if (parent->sym == from_al->sym) {
		/*
		 * At the bottom of the stack, assume the missing 'call' was
		 * before the trace started. So, pop the current symbol and push
		 * the 'to' symbol.
		 */
		if (ts->cnt == 1) {
			err = thread_stack__call_return(thread, ts, --ts->cnt,
							tm, ref, false);
			if (err)
				return err;
		}

		if (!ts->cnt) {
			cp = call_path__findnew(cpr, root, tsym, addr, ks);

			return thread_stack__push_cp(ts, addr, tm, ref, cp,
						     true, false);
		}

		/*
		 * Otherwise assume the 'return' is being used as a jump (e.g.
		 * retpoline) and just push the 'to' symbol.
		 */
		cp = call_path__findnew(cpr, parent, tsym, addr, ks);

		err = thread_stack__push_cp(ts, 0, tm, ref, cp, true, false);
		if (!err)
			ts->stack[ts->cnt - 1].non_call = true;

		return err;
	}

	/*
	 * Assume 'parent' has not yet returned, so push 'to', and then push and
	 * pop 'from'.
	 */

	cp = call_path__findnew(cpr, parent, tsym, addr, ks);

	err = thread_stack__push_cp(ts, addr, tm, ref, cp, true, false);
	if (err)
		return err;

	cp = call_path__findnew(cpr, cp, fsym, ip, ks);

	err = thread_stack__push_cp(ts, ip, tm, ref, cp, true, false);
	if (err)
		return err;

	return thread_stack__call_return(thread, ts, --ts->cnt, tm, ref, false);
}