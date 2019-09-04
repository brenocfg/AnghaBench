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
typedef  scalar_t__ u64 ;
struct thread_stack {size_t cnt; TYPE_1__* stack; } ;
struct TYPE_2__ {scalar_t__ ret_addr; } ;

/* Variables and functions */

__attribute__((used)) static void thread_stack__pop(struct thread_stack *ts, u64 ret_addr)
{
	size_t i;

	/*
	 * In some cases there may be functions which are not seen to return.
	 * For example when setjmp / longjmp has been used.  Or the perf context
	 * switch in the kernel which doesn't stop and start tracing in exactly
	 * the same code path.  When that happens the return address will be
	 * further down the stack.  If the return address is not found at all,
	 * we assume the opposite (i.e. this is a return for a call that wasn't
	 * seen for some reason) and leave the stack alone.
	 */
	for (i = ts->cnt; i; ) {
		if (ts->stack[--i].ret_addr == ret_addr) {
			ts->cnt = i;
			return;
		}
	}
}