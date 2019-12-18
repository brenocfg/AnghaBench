#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  scalar_t__ pgsocket ;
struct TYPE_12__ {size_t nevents; size_t nevents_space; int exit_on_postmaster_death; int latch_pos; TYPE_3__* latch; TYPE_2__* events; } ;
typedef  TYPE_1__ WaitEventSet ;
struct TYPE_13__ {int pos; int events; int reset; scalar_t__ fd; void* user_data; } ;
typedef  TYPE_2__ WaitEvent ;
struct TYPE_14__ {scalar_t__ owner_pid; } ;
typedef  TYPE_3__ Latch ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MyProcPid ; 
 scalar_t__ PGINVALID_SOCKET ; 
 size_t POSTMASTER_FD_WATCH ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WL_SOCKET_MASK ; 
 int /*<<< orphan*/  WaitEventAdjustEpoll (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitEventAdjustPoll (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  WaitEventAdjustWin32 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__* postmaster_alive_fds ; 
 scalar_t__ selfpipe_readfd ; 

int
AddWaitEventToSet(WaitEventSet *set, uint32 events, pgsocket fd, Latch *latch,
				  void *user_data)
{
	WaitEvent  *event;

	/* not enough space */
	Assert(set->nevents < set->nevents_space);

	if (events == WL_EXIT_ON_PM_DEATH)
	{
		events = WL_POSTMASTER_DEATH;
		set->exit_on_postmaster_death = true;
	}

	if (latch)
	{
		if (latch->owner_pid != MyProcPid)
			elog(ERROR, "cannot wait on a latch owned by another process");
		if (set->latch)
			elog(ERROR, "cannot wait on more than one latch");
		if ((events & WL_LATCH_SET) != WL_LATCH_SET)
			elog(ERROR, "latch events only support being set");
	}
	else
	{
		if (events & WL_LATCH_SET)
			elog(ERROR, "cannot wait on latch without a specified latch");
	}

	/* waiting for socket readiness without a socket indicates a bug */
	if (fd == PGINVALID_SOCKET && (events & WL_SOCKET_MASK))
		elog(ERROR, "cannot wait on socket event without a socket");

	event = &set->events[set->nevents];
	event->pos = set->nevents++;
	event->fd = fd;
	event->events = events;
	event->user_data = user_data;
#ifdef WIN32
	event->reset = false;
#endif

	if (events == WL_LATCH_SET)
	{
		set->latch = latch;
		set->latch_pos = event->pos;
#ifndef WIN32
		event->fd = selfpipe_readfd;
#endif
	}
	else if (events == WL_POSTMASTER_DEATH)
	{
#ifndef WIN32
		event->fd = postmaster_alive_fds[POSTMASTER_FD_WATCH];
#endif
	}

	/* perform wait primitive specific initialization, if needed */
#if defined(WAIT_USE_EPOLL)
	WaitEventAdjustEpoll(set, event, EPOLL_CTL_ADD);
#elif defined(WAIT_USE_POLL)
	WaitEventAdjustPoll(set, event);
#elif defined(WAIT_USE_WIN32)
	WaitEventAdjustWin32(set, event);
#endif

	return event->pos;
}