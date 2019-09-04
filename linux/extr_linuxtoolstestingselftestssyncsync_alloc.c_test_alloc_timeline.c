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
 int sw_sync_timeline_create () ; 
 int /*<<< orphan*/  sw_sync_timeline_destroy (int) ; 
 int sw_sync_timeline_is_valid (int) ; 

int test_alloc_timeline(void)
{
	int timeline, valid;

	timeline = sw_sync_timeline_create();
	valid = sw_sync_timeline_is_valid(timeline);
	ASSERT(valid, "Failure allocating timeline\n");

	sw_sync_timeline_destroy(timeline);
	return 0;
}