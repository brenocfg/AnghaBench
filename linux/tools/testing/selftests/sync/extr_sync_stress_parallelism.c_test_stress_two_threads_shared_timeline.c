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
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_2__ {int iterations; int counter; int timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int,char*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sw_sync_timeline_create () ; 
 int /*<<< orphan*/  sw_sync_timeline_destroy (int) ; 
 int sw_sync_timeline_is_valid (int) ; 
 TYPE_1__ test_data_two_threads ; 
 scalar_t__ test_stress_two_threads_shared_timeline_thread ; 

int test_stress_two_threads_shared_timeline(void)
{
	pthread_t a, b;
	int valid;
	int timeline = sw_sync_timeline_create();

	valid = sw_sync_timeline_is_valid(timeline);
	ASSERT(valid, "Failure allocating timeline\n");

	test_data_two_threads.iterations = 1 << 16;
	test_data_two_threads.counter = 0;
	test_data_two_threads.timeline = timeline;

	/*
	 * Use a single timeline to synchronize two threads
	 * hammmering on the same counter.
	 */

	pthread_create(&a, NULL, (void *(*)(void *))
		       test_stress_two_threads_shared_timeline_thread,
		       (void *)0);
	pthread_create(&b, NULL, (void *(*)(void *))
		       test_stress_two_threads_shared_timeline_thread,
		       (void *)1);

	pthread_join(a, NULL);
	pthread_join(b, NULL);

	/* make sure the threads did not trample on one another */
	ASSERT(test_data_two_threads.counter ==
	       test_data_two_threads.iterations * 2,
	       "Counter has unexpected value\n");

	sw_sync_timeline_destroy(timeline);

	return 0;
}