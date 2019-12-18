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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  pgsocket ;
typedef  int /*<<< orphan*/  WaitEventSet ;
struct TYPE_3__ {int events; } ;
typedef  TYPE_1__ WaitEvent ;
typedef  int /*<<< orphan*/  Latch ;

/* Variables and functions */
 int /*<<< orphan*/  AddWaitEventToSet (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * CreateWaitEventSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  FreeWaitEventSet (int /*<<< orphan*/ *) ; 
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  PGINVALID_SOCKET ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WL_SOCKET_MASK ; 
 int WL_TIMEOUT ; 
 int WaitEventSetWait (int /*<<< orphan*/ *,long,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
WaitLatchOrSocket(Latch *latch, int wakeEvents, pgsocket sock,
				  long timeout, uint32 wait_event_info)
{
	int			ret = 0;
	int			rc;
	WaitEvent	event;
	WaitEventSet *set = CreateWaitEventSet(CurrentMemoryContext, 3);

	if (wakeEvents & WL_TIMEOUT)
		Assert(timeout >= 0);
	else
		timeout = -1;

	if (wakeEvents & WL_LATCH_SET)
		AddWaitEventToSet(set, WL_LATCH_SET, PGINVALID_SOCKET,
						  latch, NULL);

	/* Postmaster-managed callers must handle postmaster death somehow. */
	Assert(!IsUnderPostmaster ||
		   (wakeEvents & WL_EXIT_ON_PM_DEATH) ||
		   (wakeEvents & WL_POSTMASTER_DEATH));

	if ((wakeEvents & WL_POSTMASTER_DEATH) && IsUnderPostmaster)
		AddWaitEventToSet(set, WL_POSTMASTER_DEATH, PGINVALID_SOCKET,
						  NULL, NULL);

	if ((wakeEvents & WL_EXIT_ON_PM_DEATH) && IsUnderPostmaster)
		AddWaitEventToSet(set, WL_EXIT_ON_PM_DEATH, PGINVALID_SOCKET,
						  NULL, NULL);

	if (wakeEvents & WL_SOCKET_MASK)
	{
		int			ev;

		ev = wakeEvents & WL_SOCKET_MASK;
		AddWaitEventToSet(set, ev, sock, NULL, NULL);
	}

	rc = WaitEventSetWait(set, timeout, &event, 1, wait_event_info);

	if (rc == 0)
		ret |= WL_TIMEOUT;
	else
	{
		ret |= event.events & (WL_LATCH_SET |
							   WL_POSTMASTER_DEATH |
							   WL_SOCKET_MASK);
	}

	FreeWaitEventSet(set);

	return ret;
}