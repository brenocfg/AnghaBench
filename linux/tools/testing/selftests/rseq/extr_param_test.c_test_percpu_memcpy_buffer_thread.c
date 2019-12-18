#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct percpu_memcpy_buffer_node {int dummy; } ;
struct percpu_memcpy_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ gettid () ; 
 int /*<<< orphan*/  nr_abort ; 
 int /*<<< orphan*/  opt_disable_rseq ; 
 long long opt_reps ; 
 scalar_t__ opt_yield ; 
 int /*<<< orphan*/  printf_verbose (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rseq_register_current_thread () ; 
 scalar_t__ rseq_unregister_current_thread () ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  signals_delivered ; 
 int this_cpu_memcpy_buffer_pop (struct percpu_memcpy_buffer*,struct percpu_memcpy_buffer_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_memcpy_buffer_push (struct percpu_memcpy_buffer*,struct percpu_memcpy_buffer_node,int /*<<< orphan*/ *) ; 

void *test_percpu_memcpy_buffer_thread(void *arg)
{
	long long i, reps;
	struct percpu_memcpy_buffer *buffer = (struct percpu_memcpy_buffer *)arg;

	if (!opt_disable_rseq && rseq_register_current_thread())
		abort();

	reps = opt_reps;
	for (i = 0; i < reps; i++) {
		struct percpu_memcpy_buffer_node item;
		bool result;

		result = this_cpu_memcpy_buffer_pop(buffer, &item, NULL);
		if (opt_yield)
			sched_yield();  /* encourage shuffling */
		if (result) {
			if (!this_cpu_memcpy_buffer_push(buffer, item, NULL)) {
				/* Should increase buffer size. */
				abort();
			}
		}
	}

	printf_verbose("tid %d: number of rseq abort: %d, signals delivered: %u\n",
		       (int) gettid(), nr_abort, signals_delivered);
	if (!opt_disable_rseq && rseq_unregister_current_thread())
		abort();

	return NULL;
}