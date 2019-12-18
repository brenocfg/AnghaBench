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
struct pollfd {int dummy; } ;
struct epoll_event {int dummy; } ;
struct TYPE_3__ {int nevents_space; int exit_on_postmaster_death; scalar_t__ epoll_fd; int /*<<< orphan*/ * handles; int /*<<< orphan*/ * latch; struct pollfd* pollfds; struct epoll_event* epoll_ret_events; int /*<<< orphan*/ * events; } ;
typedef  TYPE_1__ WaitEventSet ;
typedef  int /*<<< orphan*/  WaitEvent ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CLOEXEC ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 scalar_t__ MAXALIGN (int) ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StaticAssertStmt (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * WSA_INVALID_EVENT ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ epoll_create (int) ; 
 scalar_t__ epoll_create1 (int /*<<< orphan*/ ) ; 
 int fcntl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgwin32_signal_event ; 

WaitEventSet *
CreateWaitEventSet(MemoryContext context, int nevents)
{
	WaitEventSet *set;
	char	   *data;
	Size		sz = 0;

	/*
	 * Use MAXALIGN size/alignment to guarantee that later uses of memory are
	 * aligned correctly. E.g. epoll_event might need 8 byte alignment on some
	 * platforms, but earlier allocations like WaitEventSet and WaitEvent
	 * might not sized to guarantee that when purely using sizeof().
	 */
	sz += MAXALIGN(sizeof(WaitEventSet));
	sz += MAXALIGN(sizeof(WaitEvent) * nevents);

#if defined(WAIT_USE_EPOLL)
	sz += MAXALIGN(sizeof(struct epoll_event) * nevents);
#elif defined(WAIT_USE_POLL)
	sz += MAXALIGN(sizeof(struct pollfd) * nevents);
#elif defined(WAIT_USE_WIN32)
	/* need space for the pgwin32_signal_event */
	sz += MAXALIGN(sizeof(HANDLE) * (nevents + 1));
#endif

	data = (char *) MemoryContextAllocZero(context, sz);

	set = (WaitEventSet *) data;
	data += MAXALIGN(sizeof(WaitEventSet));

	set->events = (WaitEvent *) data;
	data += MAXALIGN(sizeof(WaitEvent) * nevents);

#if defined(WAIT_USE_EPOLL)
	set->epoll_ret_events = (struct epoll_event *) data;
	data += MAXALIGN(sizeof(struct epoll_event) * nevents);
#elif defined(WAIT_USE_POLL)
	set->pollfds = (struct pollfd *) data;
	data += MAXALIGN(sizeof(struct pollfd) * nevents);
#elif defined(WAIT_USE_WIN32)
	set->handles = (HANDLE) data;
	data += MAXALIGN(sizeof(HANDLE) * nevents);
#endif

	set->latch = NULL;
	set->nevents_space = nevents;
	set->exit_on_postmaster_death = false;

#if defined(WAIT_USE_EPOLL)
#ifdef EPOLL_CLOEXEC
	set->epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	if (set->epoll_fd < 0)
		elog(ERROR, "epoll_create1 failed: %m");
#else
	/* cope with ancient glibc lacking epoll_create1 (e.g., RHEL5) */
	set->epoll_fd = epoll_create(nevents);
	if (set->epoll_fd < 0)
		elog(ERROR, "epoll_create failed: %m");
	if (fcntl(set->epoll_fd, F_SETFD, FD_CLOEXEC) == -1)
		elog(ERROR, "fcntl(F_SETFD) failed on epoll descriptor: %m");
#endif							/* EPOLL_CLOEXEC */
#elif defined(WAIT_USE_WIN32)

	/*
	 * To handle signals while waiting, we need to add a win32 specific event.
	 * We accounted for the additional event at the top of this routine. See
	 * port/win32/signal.c for more details.
	 *
	 * Note: pgwin32_signal_event should be first to ensure that it will be
	 * reported when multiple events are set.  We want to guarantee that
	 * pending signals are serviced.
	 */
	set->handles[0] = pgwin32_signal_event;
	StaticAssertStmt(WSA_INVALID_EVENT == NULL, "");
#endif

	return set;
}