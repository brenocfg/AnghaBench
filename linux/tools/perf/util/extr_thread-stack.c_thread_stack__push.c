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
typedef  int /*<<< orphan*/  u64 ;
struct thread_stack {size_t cnt; size_t sz; TYPE_1__* stack; } ;
struct TYPE_2__ {int trace_end; int /*<<< orphan*/  ret_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warning (char*) ; 
 int thread_stack__grow (struct thread_stack*) ; 

__attribute__((used)) static int thread_stack__push(struct thread_stack *ts, u64 ret_addr,
			      bool trace_end)
{
	int err = 0;

	if (ts->cnt == ts->sz) {
		err = thread_stack__grow(ts);
		if (err) {
			pr_warning("Out of memory: discarding thread stack\n");
			ts->cnt = 0;
		}
	}

	ts->stack[ts->cnt].trace_end = trace_end;
	ts->stack[ts->cnt++].ret_addr = ret_addr;

	return err;
}