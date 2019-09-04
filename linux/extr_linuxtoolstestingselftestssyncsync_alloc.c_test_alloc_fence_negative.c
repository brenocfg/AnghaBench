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
 int sw_sync_timeline_create () ; 
 int /*<<< orphan*/  sw_sync_timeline_destroy (int) ; 

int test_alloc_fence_negative(void)
{
	int fence, timeline;

	timeline = sw_sync_timeline_create();
	ASSERT(timeline > 0, "Failure allocating timeline\n");

	fence = sw_sync_fence_create(-1, "fence", 1);
	ASSERT(fence < 0, "Success allocating negative fence\n");

	sw_sync_fence_destroy(fence);
	sw_sync_timeline_destroy(timeline);
	return 0;
}