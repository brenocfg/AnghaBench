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
struct perf_sample {scalar_t__ ip; scalar_t__ addr; int /*<<< orphan*/  time; } ;
struct call_path {int dummy; } ;
struct call_path_root {struct call_path call_path; } ;
struct addr_location {int /*<<< orphan*/  sym; } ;
struct TYPE_4__ {struct call_path* cp; } ;
struct TYPE_3__ {struct call_path_root* cpr; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct call_path* call_path__findnew (struct call_path_root*,struct call_path*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int thread_stack__call_return (struct thread*,struct thread_stack*,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ thread_stack__in_kernel (struct thread_stack*) ; 
 int thread_stack__pop_cp (struct thread*,struct thread_stack*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int thread_stack__push_cp (struct thread_stack*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct call_path*,int) ; 

__attribute__((used)) static int thread_stack__no_call_return(struct thread *thread,
					struct thread_stack *ts,
					struct perf_sample *sample,
					struct addr_location *from_al,
					struct addr_location *to_al, u64 ref)
{
	struct call_path_root *cpr = ts->crp->cpr;
	struct call_path *cp, *parent;
	u64 ks = ts->kernel_start;
	int err;

	if (sample->ip >= ks && sample->addr < ks) {
		/* Return to userspace, so pop all kernel addresses */
		while (thread_stack__in_kernel(ts)) {
			err = thread_stack__call_return(thread, ts, --ts->cnt,
							sample->time, ref,
							true);
			if (err)
				return err;
		}

		/* If the stack is empty, push the userspace address */
		if (!ts->cnt) {
			cp = call_path__findnew(cpr, &cpr->call_path,
						to_al->sym, sample->addr,
						ts->kernel_start);
			if (!cp)
				return -ENOMEM;
			return thread_stack__push_cp(ts, 0, sample->time, ref,
						     cp, true);
		}
	} else if (thread_stack__in_kernel(ts) && sample->ip < ks) {
		/* Return to userspace, so pop all kernel addresses */
		while (thread_stack__in_kernel(ts)) {
			err = thread_stack__call_return(thread, ts, --ts->cnt,
							sample->time, ref,
							true);
			if (err)
				return err;
		}
	}

	if (ts->cnt)
		parent = ts->stack[ts->cnt - 1].cp;
	else
		parent = &cpr->call_path;

	/* This 'return' had no 'call', so push and pop top of stack */
	cp = call_path__findnew(cpr, parent, from_al->sym, sample->ip,
				ts->kernel_start);
	if (!cp)
		return -ENOMEM;

	err = thread_stack__push_cp(ts, sample->addr, sample->time, ref, cp,
				    true);
	if (err)
		return err;

	return thread_stack__pop_cp(thread, ts, sample->addr, sample->time, ref,
				    to_al->sym);
}