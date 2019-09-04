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
struct TYPE_2__ {int timeline; int iterations; int counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int,char*) ; 
 int sw_sync_fence_create (int,char*,int) ; 
 int /*<<< orphan*/  sw_sync_fence_destroy (int) ; 
 int sw_sync_fence_is_valid (int) ; 
 int sw_sync_timeline_inc (int,int) ; 
 int sync_wait (int,int) ; 
 TYPE_1__ test_data_two_threads ; 

__attribute__((used)) static int test_stress_two_threads_shared_timeline_thread(void *d)
{
	int thread_id = (long)d;
	int timeline = test_data_two_threads.timeline;
	int iterations = test_data_two_threads.iterations;
	int fence, valid, ret, i;

	for (i = 0; i < iterations; i++) {
		fence = sw_sync_fence_create(timeline, "fence",
					     i * 2 + thread_id);
		valid = sw_sync_fence_is_valid(fence);
		ASSERT(valid, "Failure allocating fence\n");

		/* Wait on the prior thread to complete */
		ret = sync_wait(fence, -1);
		ASSERT(ret > 0, "Problem occurred on prior thread\n");

		/*
		 * Confirm the previous thread's writes are visible
		 * and then increment
		 */
		ASSERT(test_data_two_threads.counter == i * 2 + thread_id,
		       "Counter got damaged!\n");
		test_data_two_threads.counter++;

		/* Kick off the other thread */
		ret = sw_sync_timeline_inc(timeline, 1);
		ASSERT(ret == 0, "Advancing timeline failed\n");

		sw_sync_fence_destroy(fence);
	}

	return 0;
}