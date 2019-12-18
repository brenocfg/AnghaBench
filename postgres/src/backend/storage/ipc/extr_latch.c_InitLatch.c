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
struct TYPE_3__ {int is_set; int is_shared; int /*<<< orphan*/ * event; scalar_t__ owner_pid; } ;
typedef  TYPE_1__ Latch ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ selfpipe_owner_pid ; 
 scalar_t__ selfpipe_readfd ; 

void
InitLatch(Latch *latch)
{
	latch->is_set = false;
	latch->owner_pid = MyProcPid;
	latch->is_shared = false;

#ifndef WIN32
	/* Assert InitializeLatchSupport has been called in this process */
	Assert(selfpipe_readfd >= 0 && selfpipe_owner_pid == MyProcPid);
#else
	latch->event = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (latch->event == NULL)
		elog(ERROR, "CreateEvent failed: error code %lu", GetLastError());
#endif							/* WIN32 */
}