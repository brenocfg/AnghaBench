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
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int PG_SIGNAL_COUNT ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_signal_crit_sec ; 
 int /*<<< orphan*/  pg_signal_queue ; 
 int /*<<< orphan*/ * pgwin32_signal_event ; 
 int /*<<< orphan*/  sigmask (int) ; 

void
pg_queue_signal(int signum)
{
	Assert(pgwin32_signal_event != NULL);
	if (signum >= PG_SIGNAL_COUNT || signum <= 0)
		return;

	EnterCriticalSection(&pg_signal_crit_sec);
	pg_signal_queue |= sigmask(signum);
	LeaveCriticalSection(&pg_signal_crit_sec);

	SetEvent(pgwin32_signal_event);
}