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
struct spinlock_thread_test_data {long long reps; scalar_t__ reg; struct spinlock_test_data* data; } ;
struct spinlock_test_data {int /*<<< orphan*/  lock; TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ gettid () ; 
 int /*<<< orphan*/  nr_abort ; 
 int /*<<< orphan*/  opt_disable_rseq ; 
 int /*<<< orphan*/  printf_verbose (char*,int,long long,...) ; 
 int rseq_cpu_start () ; 
 int /*<<< orphan*/  rseq_percpu_unlock (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rseq_register_current_thread () ; 
 int rseq_this_cpu_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ rseq_unregister_current_thread () ; 
 int /*<<< orphan*/  signals_delivered ; 

void *test_percpu_spinlock_thread(void *arg)
{
	struct spinlock_thread_test_data *thread_data = arg;
	struct spinlock_test_data *data = thread_data->data;
	long long i, reps;

	if (!opt_disable_rseq && thread_data->reg &&
	    rseq_register_current_thread())
		abort();
	reps = thread_data->reps;
	for (i = 0; i < reps; i++) {
		int cpu = rseq_cpu_start();

		cpu = rseq_this_cpu_lock(&data->lock);
		data->c[cpu].count++;
		rseq_percpu_unlock(&data->lock, cpu);
#ifndef BENCHMARK
		if (i != 0 && !(i % (reps / 10)))
			printf_verbose("tid %d: count %lld\n", (int) gettid(), i);
#endif
	}
	printf_verbose("tid %d: number of rseq abort: %d, signals delivered: %u\n",
		       (int) gettid(), nr_abort, signals_delivered);
	if (!opt_disable_rseq && thread_data->reg &&
	    rseq_unregister_current_thread())
		abort();
	return NULL;
}