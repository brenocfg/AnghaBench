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
struct thread {int dummy; } ;
struct ip_callchain {int nr; scalar_t__* ips; } ;
struct TYPE_2__ {scalar_t__ ret_addr; } ;

/* Variables and functions */
 scalar_t__ callchain_context (scalar_t__,scalar_t__) ; 
 struct thread_stack* thread__stack (struct thread*,int) ; 

void thread_stack__sample(struct thread *thread, int cpu,
			  struct ip_callchain *chain,
			  size_t sz, u64 ip, u64 kernel_start)
{
	struct thread_stack *ts = thread__stack(thread, cpu);
	u64 context = callchain_context(ip, kernel_start);
	u64 last_context;
	size_t i, j;

	if (sz < 2) {
		chain->nr = 0;
		return;
	}

	chain->ips[0] = context;
	chain->ips[1] = ip;

	if (!ts) {
		chain->nr = 2;
		return;
	}

	last_context = context;

	for (i = 2, j = 1; i < sz && j <= ts->cnt; i++, j++) {
		ip = ts->stack[ts->cnt - j].ret_addr;
		context = callchain_context(ip, kernel_start);
		if (context != last_context) {
			if (i >= sz - 1)
				break;
			chain->ips[i++] = context;
			last_context = context;
		}
		chain->ips[i] = ip;
	}

	chain->nr = i;
}