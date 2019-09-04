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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int,char*) ; 
 int /*<<< orphan*/  FENCE_STATUS_ACTIVE ; 
 int /*<<< orphan*/  FENCE_STATUS_SIGNALED ; 
 int sw_sync_fence_create (int,char*,int) ; 
 int /*<<< orphan*/  sw_sync_fence_destroy (int) ; 
 int sw_sync_fence_is_valid (int) ; 
 int sw_sync_timeline_create () ; 
 int /*<<< orphan*/  sw_sync_timeline_destroy (int) ; 
 int sw_sync_timeline_inc (int,int) ; 
 int sync_fence_count_with_status (int,int /*<<< orphan*/ ) ; 
 int sync_merge (char*,int,int) ; 
 int sync_wait (int,int) ; 

int test_fence_multi_timeline_wait(void)
{
	int timelineA, timelineB, timelineC;
	int fenceA, fenceB, fenceC, merged;
	int valid, active, signaled, ret;

	timelineA = sw_sync_timeline_create();
	timelineB = sw_sync_timeline_create();
	timelineC = sw_sync_timeline_create();

	fenceA = sw_sync_fence_create(timelineA, "fenceA", 5);
	fenceB = sw_sync_fence_create(timelineB, "fenceB", 5);
	fenceC = sw_sync_fence_create(timelineC, "fenceC", 5);

	merged = sync_merge("mergeFence", fenceB, fenceA);
	merged = sync_merge("mergeFence", fenceC, merged);

	valid = sw_sync_fence_is_valid(merged);
	ASSERT(valid, "Failure merging fence from various timelines\n");

	/* Confirm fence isn't signaled */
	active = sync_fence_count_with_status(merged, FENCE_STATUS_ACTIVE);
	ASSERT(active == 3, "Fence signaled too early!\n");

	ret = sync_wait(merged, 0);
	ASSERT(ret == 0,
	       "Failure waiting on fence until timeout\n");

	ret = sw_sync_timeline_inc(timelineA, 5);
	active = sync_fence_count_with_status(merged, FENCE_STATUS_ACTIVE);
	signaled = sync_fence_count_with_status(merged, FENCE_STATUS_SIGNALED);
	ASSERT(active == 2 && signaled == 1,
	       "Fence did not signal properly!\n");

	ret = sw_sync_timeline_inc(timelineB, 5);
	active = sync_fence_count_with_status(merged, FENCE_STATUS_ACTIVE);
	signaled = sync_fence_count_with_status(merged, FENCE_STATUS_SIGNALED);
	ASSERT(active == 1 && signaled == 2,
	       "Fence did not signal properly!\n");

	ret = sw_sync_timeline_inc(timelineC, 5);
	active = sync_fence_count_with_status(merged, FENCE_STATUS_ACTIVE);
	signaled = sync_fence_count_with_status(merged, FENCE_STATUS_SIGNALED);
	ASSERT(active == 0 && signaled == 3,
	       "Fence did not signal properly!\n");

	/* confirm you can successfully wait */
	ret = sync_wait(merged, 100);
	ASSERT(ret > 0, "Failure waiting on signaled fence\n");

	sw_sync_fence_destroy(merged);
	sw_sync_fence_destroy(fenceC);
	sw_sync_fence_destroy(fenceB);
	sw_sync_fence_destroy(fenceA);
	sw_sync_timeline_destroy(timelineC);
	sw_sync_timeline_destroy(timelineB);
	sw_sync_timeline_destroy(timelineA);

	return 0;
}