#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fin_time; size_t index; } ;
typedef  TYPE_1__ timeout_params ;
typedef  scalar_t__ TimestampTz ;
typedef  size_t TimeoutId ;
struct TYPE_5__ {int indicator; scalar_t__ fin_time; scalar_t__ start_time; scalar_t__ active; int /*<<< orphan*/ * timeout_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_1__** active_timeouts ; 
 TYPE_2__* all_timeouts ; 
 int /*<<< orphan*/  all_timeouts_initialized ; 
 int /*<<< orphan*/  find_active_timeout (size_t) ; 
 int /*<<< orphan*/  insert_timeout (size_t,int) ; 
 int num_active_timeouts ; 
 int /*<<< orphan*/  remove_timeout_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_timeout(TimeoutId id, TimestampTz now, TimestampTz fin_time)
{
	int			i;

	/* Assert request is sane */
	Assert(all_timeouts_initialized);
	Assert(all_timeouts[id].timeout_handler != NULL);

	/*
	 * If this timeout was already active, momentarily disable it.  We
	 * interpret the call as a directive to reschedule the timeout.
	 */
	if (all_timeouts[id].active)
		remove_timeout_index(find_active_timeout(id));

	/*
	 * Find out the index where to insert the new timeout.  We sort by
	 * fin_time, and for equal fin_time by priority.
	 */
	for (i = 0; i < num_active_timeouts; i++)
	{
		timeout_params *old_timeout = active_timeouts[i];

		if (fin_time < old_timeout->fin_time)
			break;
		if (fin_time == old_timeout->fin_time && id < old_timeout->index)
			break;
	}

	/*
	 * Mark the timeout active, and insert it into the active list.
	 */
	all_timeouts[id].indicator = false;
	all_timeouts[id].start_time = now;
	all_timeouts[id].fin_time = fin_time;

	insert_timeout(id, i);
}