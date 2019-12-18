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
 int sw_sync_fence_create (int,char*,int) ; 
 int /*<<< orphan*/  sw_sync_fence_destroy (int) ; 
 int sw_sync_fence_is_valid (int) ; 
 int sw_sync_timeline_create () ; 
 int /*<<< orphan*/  sw_sync_timeline_destroy (int) ; 
 int sw_sync_timeline_is_valid (int) ; 

int test_alloc_fence(void)
{
	int timeline, fence, valid;

	timeline = sw_sync_timeline_create();
	valid = sw_sync_timeline_is_valid(timeline);
	ASSERT(valid, "Failure allocating timeline\n");

	fence = sw_sync_fence_create(timeline, "allocFence", 1);
	valid = sw_sync_fence_is_valid(fence);
	ASSERT(valid, "Failure allocating fence\n");

	sw_sync_fence_destroy(fence);
	sw_sync_timeline_destroy(timeline);
	return 0;
}