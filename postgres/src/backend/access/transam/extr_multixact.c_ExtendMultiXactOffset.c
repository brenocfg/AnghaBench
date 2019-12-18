#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ MultiXactId ;

/* Variables and functions */
 scalar_t__ FirstMultiXactId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MultiXactIdToOffsetEntry (scalar_t__) ; 
 int MultiXactIdToOffsetPage (scalar_t__) ; 
 int /*<<< orphan*/  MultiXactOffsetControlLock ; 
 int /*<<< orphan*/  ZeroMultiXactOffsetPage (int,int) ; 

__attribute__((used)) static void
ExtendMultiXactOffset(MultiXactId multi)
{
	int			pageno;

	/*
	 * No work except at first MultiXactId of a page.  But beware: just after
	 * wraparound, the first MultiXactId of page zero is FirstMultiXactId.
	 */
	if (MultiXactIdToOffsetEntry(multi) != 0 &&
		multi != FirstMultiXactId)
		return;

	pageno = MultiXactIdToOffsetPage(multi);

	LWLockAcquire(MultiXactOffsetControlLock, LW_EXCLUSIVE);

	/* Zero the page and make an XLOG entry about it */
	ZeroMultiXactOffsetPage(pageno, true);

	LWLockRelease(MultiXactOffsetControlLock);
}