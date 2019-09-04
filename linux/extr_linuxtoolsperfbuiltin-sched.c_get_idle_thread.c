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
struct thread {int dummy; } ;

/* Variables and functions */
 int __roundup_pow_of_two (int) ; 
 int idle_max_cpu ; 
 struct thread** idle_threads ; 
 scalar_t__ init_idle_thread (struct thread*) ; 
 void* realloc (struct thread**,int) ; 
 struct thread* thread__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct thread *get_idle_thread(int cpu)
{
	/*
	 * expand/allocate array of pointers to local thread
	 * structs if needed
	 */
	if ((cpu >= idle_max_cpu) || (idle_threads == NULL)) {
		int i, j = __roundup_pow_of_two(cpu+1);
		void *p;

		p = realloc(idle_threads, j * sizeof(struct thread *));
		if (!p)
			return NULL;

		idle_threads = (struct thread **) p;
		for (i = idle_max_cpu; i < j; ++i)
			idle_threads[i] = NULL;

		idle_max_cpu = j;
	}

	/* allocate a new thread struct if needed */
	if (idle_threads[cpu] == NULL) {
		idle_threads[cpu] = thread__new(0, 0);

		if (idle_threads[cpu]) {
			if (init_idle_thread(idle_threads[cpu]) < 0)
				return NULL;
		}
	}

	return idle_threads[cpu];
}