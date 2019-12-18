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
struct TYPE_6__ {TYPE_1__* shared; } ;
struct TYPE_5__ {int /*<<< orphan*/ * page_dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  MultiXactMemberControlLock ; 
 TYPE_2__* MultiXactMemberCtl ; 
 int /*<<< orphan*/  MultiXactOffsetControlLock ; 
 TYPE_2__* MultiXactOffsetCtl ; 
 int /*<<< orphan*/  SimpleLruWritePage (TYPE_2__*,int) ; 
 int ZeroMultiXactMemberPage (int /*<<< orphan*/ ,int) ; 
 int ZeroMultiXactOffsetPage (int /*<<< orphan*/ ,int) ; 

void
BootStrapMultiXact(void)
{
	int			slotno;

	LWLockAcquire(MultiXactOffsetControlLock, LW_EXCLUSIVE);

	/* Create and zero the first page of the offsets log */
	slotno = ZeroMultiXactOffsetPage(0, false);

	/* Make sure it's written out */
	SimpleLruWritePage(MultiXactOffsetCtl, slotno);
	Assert(!MultiXactOffsetCtl->shared->page_dirty[slotno]);

	LWLockRelease(MultiXactOffsetControlLock);

	LWLockAcquire(MultiXactMemberControlLock, LW_EXCLUSIVE);

	/* Create and zero the first page of the members log */
	slotno = ZeroMultiXactMemberPage(0, false);

	/* Make sure it's written out */
	SimpleLruWritePage(MultiXactMemberCtl, slotno);
	Assert(!MultiXactMemberCtl->shared->page_dirty[slotno]);

	LWLockRelease(MultiXactMemberControlLock);
}