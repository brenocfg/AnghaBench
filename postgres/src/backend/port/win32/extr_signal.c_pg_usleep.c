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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pgwin32_dispatch_queued_signals () ; 
 int /*<<< orphan*/ * pgwin32_signal_event ; 

void
pg_usleep(long microsec)
{
	Assert(pgwin32_signal_event != NULL);
	if (WaitForSingleObject(pgwin32_signal_event,
							(microsec < 500 ? 1 : (microsec + 500) / 1000))
		== WAIT_OBJECT_0)
	{
		pgwin32_dispatch_queued_signals();
		errno = EINTR;
		return;
	}
}