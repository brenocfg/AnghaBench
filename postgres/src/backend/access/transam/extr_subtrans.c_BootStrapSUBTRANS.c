#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* shared; } ;
struct TYPE_4__ {int /*<<< orphan*/ * page_dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  SimpleLruWritePage (TYPE_2__*,int) ; 
 TYPE_2__* SubTransCtl ; 
 int /*<<< orphan*/  SubtransControlLock ; 
 int ZeroSUBTRANSPage (int /*<<< orphan*/ ) ; 

void
BootStrapSUBTRANS(void)
{
	int			slotno;

	LWLockAcquire(SubtransControlLock, LW_EXCLUSIVE);

	/* Create and zero the first page of the subtrans log */
	slotno = ZeroSUBTRANSPage(0);

	/* Make sure it's written out */
	SimpleLruWritePage(SubTransCtl, slotno);
	Assert(!SubTransCtl->shared->page_dirty[slotno]);

	LWLockRelease(SubtransControlLock);
}