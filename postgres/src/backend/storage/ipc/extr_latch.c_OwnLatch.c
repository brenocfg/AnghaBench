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
struct TYPE_3__ {int is_shared; scalar_t__ owner_pid; } ;
typedef  TYPE_1__ Latch ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ selfpipe_owner_pid ; 
 scalar_t__ selfpipe_readfd ; 

void
OwnLatch(Latch *latch)
{
	/* Sanity checks */
	Assert(latch->is_shared);

#ifndef WIN32
	/* Assert InitializeLatchSupport has been called in this process */
	Assert(selfpipe_readfd >= 0 && selfpipe_owner_pid == MyProcPid);
#endif

	if (latch->owner_pid != 0)
		elog(ERROR, "latch already owned");

	latch->owner_pid = MyProcPid;
}