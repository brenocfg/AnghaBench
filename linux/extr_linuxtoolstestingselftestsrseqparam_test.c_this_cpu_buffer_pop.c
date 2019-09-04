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
struct percpu_buffer_node {int dummy; } ;
struct percpu_buffer {TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/ * array; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 struct percpu_buffer_node* RSEQ_READ_ONCE (int /*<<< orphan*/ ) ; 
 int rseq_cmpeqv_cmpeqv_storev (intptr_t*,intptr_t,intptr_t*,intptr_t,intptr_t,int) ; 
 int rseq_cpu_start () ; 
 scalar_t__ rseq_likely (int) ; 

struct percpu_buffer_node *this_cpu_buffer_pop(struct percpu_buffer *buffer,
					       int *_cpu)
{
	struct percpu_buffer_node *head;
	int cpu;

	for (;;) {
		intptr_t *targetptr, newval;
		intptr_t offset;
		int ret;

		cpu = rseq_cpu_start();
		/* Load offset with single-copy atomicity. */
		offset = RSEQ_READ_ONCE(buffer->c[cpu].offset);
		if (offset == 0) {
			head = NULL;
			break;
		}
		head = RSEQ_READ_ONCE(buffer->c[cpu].array[offset - 1]);
		newval = offset - 1;
		targetptr = (intptr_t *)&buffer->c[cpu].offset;
		ret = rseq_cmpeqv_cmpeqv_storev(targetptr, offset,
			(intptr_t *)&buffer->c[cpu].array[offset - 1],
			(intptr_t)head, newval, cpu);
		if (rseq_likely(!ret))
			break;
		/* Retry if comparison fails or rseq aborts. */
	}
	if (_cpu)
		*_cpu = cpu;
	return head;
}