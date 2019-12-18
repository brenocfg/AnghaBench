#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_10__ {int nevents; int /*<<< orphan*/ * latch; TYPE_2__* events; } ;
typedef  TYPE_1__ WaitEventSet ;
struct TYPE_11__ {int events; } ;
typedef  TYPE_2__ WaitEvent ;
typedef  int /*<<< orphan*/  Latch ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EPOLL_CTL_MOD ; 
 int /*<<< orphan*/  ERROR ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int /*<<< orphan*/  WaitEventAdjustEpoll (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitEventAdjustPoll (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  WaitEventAdjustWin32 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
ModifyWaitEvent(WaitEventSet *set, int pos, uint32 events, Latch *latch)
{
	WaitEvent  *event;

	Assert(pos < set->nevents);

	event = &set->events[pos];

	/*
	 * If neither the event mask nor the associated latch changes, return
	 * early. That's an important optimization for some sockets, where
	 * ModifyWaitEvent is frequently used to switch from waiting for reads to
	 * waiting on writes.
	 */
	if (events == event->events &&
		(!(event->events & WL_LATCH_SET) || set->latch == latch))
		return;

	if (event->events & WL_LATCH_SET &&
		events != event->events)
	{
		/* we could allow to disable latch events for a while */
		elog(ERROR, "cannot modify latch event");
	}

	if (event->events & WL_POSTMASTER_DEATH)
	{
		elog(ERROR, "cannot modify postmaster death event");
	}

	/* FIXME: validate event mask */
	event->events = events;

	if (events == WL_LATCH_SET)
	{
		set->latch = latch;
	}

#if defined(WAIT_USE_EPOLL)
	WaitEventAdjustEpoll(set, event, EPOLL_CTL_MOD);
#elif defined(WAIT_USE_POLL)
	WaitEventAdjustPoll(set, event);
#elif defined(WAIT_USE_WIN32)
	WaitEventAdjustWin32(set, event);
#endif
}