#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * triggerlist; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  EventTriggerEvent ;
typedef  TYPE_1__ EventTriggerCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  BuildEventTriggerCache () ; 
 scalar_t__ ETCS_VALID ; 
 int /*<<< orphan*/  EventTriggerCache ; 
 scalar_t__ EventTriggerCacheState ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/ * NIL ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

List *
EventCacheLookup(EventTriggerEvent event)
{
	EventTriggerCacheEntry *entry;

	if (EventTriggerCacheState != ETCS_VALID)
		BuildEventTriggerCache();
	entry = hash_search(EventTriggerCache, &event, HASH_FIND, NULL);
	return entry != NULL ? entry->triggerlist : NIL;
}