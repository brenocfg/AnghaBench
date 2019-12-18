#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_stack_entry {struct call_path* cp; } ;
struct thread_stack {int cnt; struct thread_stack_entry* stack; int /*<<< orphan*/  kernel_start; TYPE_1__* crp; } ;
struct symbol {scalar_t__ start; int /*<<< orphan*/  name; } ;
struct perf_sample {int /*<<< orphan*/  addr; } ;
struct call_path_root {int dummy; } ;
struct call_path {struct symbol* sym; } ;
struct addr_location {scalar_t__ addr; struct symbol* sym; } ;
struct TYPE_2__ {struct call_path_root* cpr; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct call_path* call_path__findnew (struct call_path_root*,struct call_path*,struct symbol*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_x86_retpoline (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thread_stack__x86_retpoline(struct thread_stack *ts,
				       struct perf_sample *sample,
				       struct addr_location *to_al)
{
	struct thread_stack_entry *tse = &ts->stack[ts->cnt - 1];
	struct call_path_root *cpr = ts->crp->cpr;
	struct symbol *sym = tse->cp->sym;
	struct symbol *tsym = to_al->sym;
	struct call_path *cp;

	if (sym && is_x86_retpoline(sym->name)) {
		/*
		 * This is a x86 retpoline fn. It pollutes the call graph by
		 * showing up everywhere there is an indirect branch, but does
		 * not itself mean anything. Here the top-of-stack is removed,
		 * by decrementing the stack count, and then further down, the
		 * resulting top-of-stack is replaced with the actual target.
		 * The result is that the retpoline functions will no longer
		 * appear in the call graph. Note this only affects the call
		 * graph, since all the original branches are left unchanged.
		 */
		ts->cnt -= 1;
		sym = ts->stack[ts->cnt - 2].cp->sym;
		if (sym && sym == tsym && to_al->addr != tsym->start) {
			/*
			 * Target is back to the middle of the symbol we came
			 * from so assume it is an indirect jmp and forget it
			 * altogether.
			 */
			ts->cnt -= 1;
			return 0;
		}
	} else if (sym && sym == tsym) {
		/*
		 * Target is back to the symbol we came from so assume it is an
		 * indirect jmp and forget it altogether.
		 */
		ts->cnt -= 1;
		return 0;
	}

	cp = call_path__findnew(cpr, ts->stack[ts->cnt - 2].cp, tsym,
				sample->addr, ts->kernel_start);
	if (!cp)
		return -ENOMEM;

	/* Replace the top-of-stack with the actual target */
	ts->stack[ts->cnt - 1].cp = cp;

	return 0;
}