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
 int sw_sync_timeline_inc (int,int) ; 
 int sw_sync_timeline_is_valid (int) ; 
 int sync_wait (int,int /*<<< orphan*/ ) ; 

int test_fence_one_timeline_wait(void)
{
	int fence, valid, ret;
	int timeline = sw_sync_timeline_create();

	valid = sw_sync_timeline_is_valid(timeline);
	ASSERT(valid, "Failure allocating timeline\n");

	fence = sw_sync_fence_create(timeline, "allocFence", 5);
	valid = sw_sync_fence_is_valid(fence);
	ASSERT(valid, "Failure allocating fence\n");

	/* Wait on fence until timeout */
	ret = sync_wait(fence, 0);
	ASSERT(ret == 0, "Failure waiting on fence until timeout\n");

	/* Advance timeline from 0 -> 1 */
	ret = sw_sync_timeline_inc(timeline, 1);
	ASSERT(ret == 0, "Failure advancing timeline\n");

	/* Wait on fence until timeout */
	ret = sync_wait(fence, 0);
	ASSERT(ret == 0, "Failure waiting on fence until timeout\n");

	/* Signal the fence */
	ret = sw_sync_timeline_inc(timeline, 4);
	ASSERT(ret == 0, "Failure signaling the fence\n");

	/* Wait successfully */
	ret = sync_wait(fence, 0);
	ASSERT(ret > 0, "Failure waiting on fence\n");

	/* Go even further, and confirm wait still succeeds */
	ret = sw_sync_timeline_inc(timeline, 10);
	ASSERT(ret == 0, "Failure going further\n");
	ret = sync_wait(fence, 0);
	ASSERT(ret > 0, "Failure waiting ahead\n");

	sw_sync_fence_destroy(fence);
	sw_sync_timeline_destroy(timeline);

	return 0;
}