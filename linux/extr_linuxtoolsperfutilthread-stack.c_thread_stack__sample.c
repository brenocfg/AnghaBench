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
struct thread {TYPE_2__* ts; } ;
struct ip_callchain {int nr; scalar_t__* ips; } ;
struct TYPE_4__ {size_t cnt; TYPE_1__* stack; } ;
struct TYPE_3__ {scalar_t__ ret_addr; } ;

/* Variables and functions */
 scalar_t__ callchain_context (scalar_t__,scalar_t__) ; 

void thread_stack__sample(struct thread *thread, struct ip_callchain *chain,
			  size_t sz, u64 ip, u64 kernel_start)
{
	u64 context = callchain_context(ip, kernel_start);
	u64 last_context;
	size_t i, j;

	if (sz < 2) {
		chain->nr = 0;
		return;
	}

	chain->ips[0] = context;
	chain->ips[1] = ip;

	if (!thread || !thread->ts) {
		chain->nr = 2;
		return;
	}

	last_context = context;

	for (i = 2, j = 1; i < sz && j <= thread->ts->cnt; i++, j++) {
		ip = thread->ts->stack[thread->ts->cnt - j].ret_addr;
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