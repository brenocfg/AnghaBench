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
struct thread_stack {size_t cnt; TYPE_1__* stack; } ;
struct TYPE_2__ {scalar_t__ trace_end; } ;

/* Variables and functions */

__attribute__((used)) static void thread_stack__pop_trace_end(struct thread_stack *ts)
{
	size_t i;

	for (i = ts->cnt; i; ) {
		if (ts->stack[--i].trace_end)
			ts->cnt = i;
		else
			return;
	}
}