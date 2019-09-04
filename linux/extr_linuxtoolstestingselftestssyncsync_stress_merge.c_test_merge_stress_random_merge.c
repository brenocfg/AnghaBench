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
typedef  int /*<<< orphan*/  fence_map ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int,char*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int sw_sync_fence_create (int,char*,int) ; 
 int /*<<< orphan*/  sw_sync_fence_destroy (int) ; 
 int sw_sync_fence_is_valid (int) ; 
 int sw_sync_timeline_create () ; 
 int /*<<< orphan*/  sw_sync_timeline_destroy (int) ; 
 int /*<<< orphan*/  sw_sync_timeline_inc (int,int) ; 
 int sync_fence_size (int) ; 
 int sync_merge (char*,int,int) ; 
 int sync_wait (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int test_merge_stress_random_merge(void)
{
	int i, size, ret;
	int timeline_count = 32;
	int merge_count = 1024 * 32;
	int timelines[timeline_count];
	int fence_map[timeline_count];
	int fence, tmpfence, merged, valid;
	int timeline, timeline_offset, sync_point;

	srand(time(NULL));

	for (i = 0; i < timeline_count; i++)
		timelines[i] = sw_sync_timeline_create();

	fence = sw_sync_fence_create(timelines[0], "fence", 0);
	valid = sw_sync_fence_is_valid(fence);
	ASSERT(valid, "Failure creating fence\n");

	memset(fence_map, -1, sizeof(fence_map));
	fence_map[0] = 0;

	/*
	 * Randomly create sync_points out of a fixed set of timelines,
	 * and merge them together
	 */
	for (i = 0; i < merge_count; i++) {
		/* Generate sync_point. */
		timeline_offset = rand() % timeline_count;
		timeline = timelines[timeline_offset];
		sync_point = rand();

		/* Keep track of the latest sync_point in each timeline. */
		if (fence_map[timeline_offset] == -1)
			fence_map[timeline_offset] = sync_point;
		else if (fence_map[timeline_offset] < sync_point)
			fence_map[timeline_offset] = sync_point;

		/* Merge */
		tmpfence = sw_sync_fence_create(timeline, "fence", sync_point);
		merged = sync_merge("merge", tmpfence, fence);
		sw_sync_fence_destroy(tmpfence);
		sw_sync_fence_destroy(fence);
		fence = merged;

		valid = sw_sync_fence_is_valid(merged);
		ASSERT(valid, "Failure creating fence i\n");
	}

	size = 0;
	for (i = 0; i < timeline_count; i++)
		if (fence_map[i] != -1)
			size++;

	/* Confirm our map matches the fence. */
	ASSERT(sync_fence_size(fence) == size,
	       "Quantity of elements not matching\n");

	/* Trigger the merged fence */
	for (i = 0; i < timeline_count; i++) {
		if (fence_map[i] != -1) {
			ret = sync_wait(fence, 0);
			ASSERT(ret == 0,
			       "Failure waiting on fence until timeout\n");
			/* Increment the timeline to the last sync_point */
			sw_sync_timeline_inc(timelines[i], fence_map[i]);
		}
	}

	/* Check that the fence is triggered. */
	ret = sync_wait(fence, 0);
	ASSERT(ret > 0, "Failure triggering fence\n");

	sw_sync_fence_destroy(fence);

	for (i = 0; i < timeline_count; i++)
		sw_sync_timeline_destroy(timelines[i]);

	return 0;
}