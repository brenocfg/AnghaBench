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
typedef  int /*<<< orphan*/ * timeout_handler_proc ;
typedef  size_t TimeoutId ;
struct TYPE_2__ {int /*<<< orphan*/ * timeout_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_CONFIGURATION_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  FATAL ; 
 size_t MAX_TIMEOUTS ; 
 size_t USER_TIMEOUT ; 
 TYPE_1__* all_timeouts ; 
 int /*<<< orphan*/  all_timeouts_initialized ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

TimeoutId
RegisterTimeout(TimeoutId id, timeout_handler_proc handler)
{
	Assert(all_timeouts_initialized);

	/* There's no need to disable the signal handler here. */

	if (id >= USER_TIMEOUT)
	{
		/* Allocate a user-defined timeout reason */
		for (id = USER_TIMEOUT; id < MAX_TIMEOUTS; id++)
			if (all_timeouts[id].timeout_handler == NULL)
				break;
		if (id >= MAX_TIMEOUTS)
			ereport(FATAL,
					(errcode(ERRCODE_CONFIGURATION_LIMIT_EXCEEDED),
					 errmsg("cannot add more timeout reasons")));
	}

	Assert(all_timeouts[id].timeout_handler == NULL);

	all_timeouts[id].timeout_handler = handler;

	return id;
}