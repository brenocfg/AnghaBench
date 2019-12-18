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
struct percpu_list_node {struct percpu_list_node* next; } ;
struct percpu_list {TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 scalar_t__ RSEQ_READ_ONCE (int /*<<< orphan*/ ) ; 
 int rseq_cmpeqv_storev (intptr_t*,intptr_t,intptr_t,int) ; 
 int rseq_cpu_start () ; 
 scalar_t__ rseq_likely (int) ; 

void this_cpu_list_push(struct percpu_list *list,
			struct percpu_list_node *node,
			int *_cpu)
{
	int cpu;

	for (;;) {
		intptr_t *targetptr, newval, expect;
		int ret;

		cpu = rseq_cpu_start();
		/* Load list->c[cpu].head with single-copy atomicity. */
		expect = (intptr_t)RSEQ_READ_ONCE(list->c[cpu].head);
		newval = (intptr_t)node;
		targetptr = (intptr_t *)&list->c[cpu].head;
		node->next = (struct percpu_list_node *)expect;
		ret = rseq_cmpeqv_storev(targetptr, expect, newval, cpu);
		if (rseq_likely(!ret))
			break;
		/* Retry if comparison fails or rseq aborts. */
	}
	if (_cpu)
		*_cpu = cpu;
}