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
struct TYPE_2__ {int /*<<< orphan*/  procLatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FeBeWaitSet ; 
 int /*<<< orphan*/  LocalLatchData ; 
 int /*<<< orphan*/  ModifyWaitEvent (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MyLatch ; 
 TYPE_1__* MyProc ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WL_LATCH_SET ; 

void
SwitchToSharedLatch(void)
{
	Assert(MyLatch == &LocalLatchData);
	Assert(MyProc != NULL);

	MyLatch = &MyProc->procLatch;

	if (FeBeWaitSet)
		ModifyWaitEvent(FeBeWaitSet, 1, WL_LATCH_SET, MyLatch);

	/*
	 * Set the shared latch as the local one might have been set. This
	 * shouldn't normally be necessary as code is supposed to check the
	 * condition before waiting for the latch, but a bit care can't hurt.
	 */
	SetLatch(MyLatch);
}