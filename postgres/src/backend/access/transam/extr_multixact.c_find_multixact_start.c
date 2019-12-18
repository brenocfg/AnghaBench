#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  finishedStartup; } ;
struct TYPE_9__ {TYPE_1__* shared; } ;
struct TYPE_8__ {scalar_t__* page_buffer; } ;
typedef  int /*<<< orphan*/  MultiXactOffset ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int MultiXactIdToOffsetEntry (int /*<<< orphan*/ ) ; 
 int MultiXactIdToOffsetPage (int /*<<< orphan*/ ) ; 
 TYPE_2__* MultiXactMemberCtl ; 
 int /*<<< orphan*/  MultiXactOffsetControlLock ; 
 TYPE_2__* MultiXactOffsetCtl ; 
 TYPE_5__* MultiXactState ; 
 int /*<<< orphan*/  SimpleLruDoesPhysicalPageExist (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SimpleLruFlush (TYPE_2__*,int) ; 
 int SimpleLruReadPage_ReadOnly (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
find_multixact_start(MultiXactId multi, MultiXactOffset *result)
{
	MultiXactOffset offset;
	int			pageno;
	int			entryno;
	int			slotno;
	MultiXactOffset *offptr;

	Assert(MultiXactState->finishedStartup);

	pageno = MultiXactIdToOffsetPage(multi);
	entryno = MultiXactIdToOffsetEntry(multi);

	/*
	 * Flush out dirty data, so PhysicalPageExists can work correctly.
	 * SimpleLruFlush() is a pretty big hammer for that.  Alternatively we
	 * could add an in-memory version of page exists, but find_multixact_start
	 * is called infrequently, and it doesn't seem bad to flush buffers to
	 * disk before truncation.
	 */
	SimpleLruFlush(MultiXactOffsetCtl, true);
	SimpleLruFlush(MultiXactMemberCtl, true);

	if (!SimpleLruDoesPhysicalPageExist(MultiXactOffsetCtl, pageno))
		return false;

	/* lock is acquired by SimpleLruReadPage_ReadOnly */
	slotno = SimpleLruReadPage_ReadOnly(MultiXactOffsetCtl, pageno, multi);
	offptr = (MultiXactOffset *) MultiXactOffsetCtl->shared->page_buffer[slotno];
	offptr += entryno;
	offset = *offptr;
	LWLockRelease(MultiXactOffsetControlLock);

	*result = offset;
	return true;
}