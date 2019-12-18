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
struct spinlock_test_data {int reps; int /*<<< orphan*/  lock; TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  rseq_percpu_unlock (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rseq_register_current_thread () ; 
 int rseq_this_cpu_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ rseq_unregister_current_thread () ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

void *test_percpu_spinlock_thread(void *arg)
{
	struct spinlock_test_data *data = arg;
	int i, cpu;

	if (rseq_register_current_thread()) {
		fprintf(stderr, "Error: rseq_register_current_thread(...) failed(%d): %s\n",
			errno, strerror(errno));
		abort();
	}
	for (i = 0; i < data->reps; i++) {
		cpu = rseq_this_cpu_lock(&data->lock);
		data->c[cpu].count++;
		rseq_percpu_unlock(&data->lock, cpu);
	}
	if (rseq_unregister_current_thread()) {
		fprintf(stderr, "Error: rseq_unregister_current_thread(...) failed(%d): %s\n",
			errno, strerror(errno));
		abort();
	}

	return NULL;
}