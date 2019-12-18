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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ ETCS_NEEDS_REBUILD ; 
 scalar_t__ ETCS_VALID ; 
 int /*<<< orphan*/ * EventTriggerCache ; 
 int /*<<< orphan*/  EventTriggerCacheContext ; 
 scalar_t__ EventTriggerCacheState ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
InvalidateEventCacheCallback(Datum arg, int cacheid, uint32 hashvalue)
{
	/*
	 * If the cache isn't valid, then there might be a rebuild in progress, so
	 * we can't immediately blow it away.  But it's advantageous to do this
	 * when possible, so as to immediately free memory.
	 */
	if (EventTriggerCacheState == ETCS_VALID)
	{
		MemoryContextResetAndDeleteChildren(EventTriggerCacheContext);
		EventTriggerCache = NULL;
	}

	/* Mark cache for rebuild. */
	EventTriggerCacheState = ETCS_NEEDS_REBUILD;
}