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
struct thread_stack {int cnt; int /*<<< orphan*/  kernel_start; TYPE_1__* stack; TYPE_2__* crp; } ;
struct perf_sample {int /*<<< orphan*/  time; scalar_t__ insn_len; scalar_t__ ip; } ;
struct call_path_root {int dummy; } ;
struct call_path {int dummy; } ;
struct TYPE_4__ {struct call_path_root* cpr; } ;
struct TYPE_3__ {int /*<<< orphan*/  cp; scalar_t__ ref; } ;

/* Variables and functions */
 struct call_path* call_path__findnew (struct call_path_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int thread_stack__push_cp (struct thread_stack*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct call_path*,int,int) ; 

__attribute__((used)) static int thread_stack__trace_end(struct thread_stack *ts,
				   struct perf_sample *sample, u64 ref)
{
	struct call_path_root *cpr = ts->crp->cpr;
	struct call_path *cp;
	u64 ret_addr;

	/* No point having 'trace end' on the bottom of the stack */
	if (!ts->cnt || (ts->cnt == 1 && ts->stack[0].ref == ref))
		return 0;

	cp = call_path__findnew(cpr, ts->stack[ts->cnt - 1].cp, NULL, 0,
				ts->kernel_start);

	ret_addr = sample->ip + sample->insn_len;

	return thread_stack__push_cp(ts, ret_addr, sample->time, ref, cp,
				     false, true);
}