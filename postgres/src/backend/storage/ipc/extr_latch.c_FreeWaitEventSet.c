#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nevents; int /*<<< orphan*/ * handles; TYPE_2__* events; int /*<<< orphan*/  epoll_fd; } ;
typedef  TYPE_1__ WaitEventSet ;
struct TYPE_6__ {int events; int pos; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ WaitEvent ;

/* Variables and functions */
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int /*<<< orphan*/  WSACloseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAEventSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
FreeWaitEventSet(WaitEventSet *set)
{
#if defined(WAIT_USE_EPOLL)
	close(set->epoll_fd);
#elif defined(WAIT_USE_WIN32)
	WaitEvent  *cur_event;

	for (cur_event = set->events;
		 cur_event < (set->events + set->nevents);
		 cur_event++)
	{
		if (cur_event->events & WL_LATCH_SET)
		{
			/* uses the latch's HANDLE */
		}
		else if (cur_event->events & WL_POSTMASTER_DEATH)
		{
			/* uses PostmasterHandle */
		}
		else
		{
			/* Clean up the event object we created for the socket */
			WSAEventSelect(cur_event->fd, NULL, 0);
			WSACloseEvent(set->handles[cur_event->pos + 1]);
		}
	}
#endif

	pfree(set);
}