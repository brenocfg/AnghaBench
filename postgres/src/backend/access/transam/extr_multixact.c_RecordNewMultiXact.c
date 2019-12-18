#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_9__ {TYPE_1__* shared; } ;
struct TYPE_8__ {int status; int /*<<< orphan*/  xid; } ;
struct TYPE_7__ {int* page_dirty; scalar_t__* page_buffer; } ;
typedef  int /*<<< orphan*/  MultiXactOffset ;
typedef  TYPE_2__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MXACT_MEMBER_BITS_PER_XACT ; 
 int MXOffsetToFlagsBitShift (int /*<<< orphan*/ ) ; 
 int MXOffsetToFlagsOffset (int /*<<< orphan*/ ) ; 
 int MXOffsetToMemberOffset (int /*<<< orphan*/ ) ; 
 int MXOffsetToMemberPage (int /*<<< orphan*/ ) ; 
 int MultiXactIdToOffsetEntry (int /*<<< orphan*/ ) ; 
 int MultiXactIdToOffsetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiXactMemberControlLock ; 
 TYPE_3__* MultiXactMemberCtl ; 
 int /*<<< orphan*/  MultiXactOffsetControlLock ; 
 TYPE_3__* MultiXactOffsetCtl ; 
 int MultiXactStatusUpdate ; 
 int SimpleLruReadPage (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RecordNewMultiXact(MultiXactId multi, MultiXactOffset offset,
				   int nmembers, MultiXactMember *members)
{
	int			pageno;
	int			prev_pageno;
	int			entryno;
	int			slotno;
	MultiXactOffset *offptr;
	int			i;

	LWLockAcquire(MultiXactOffsetControlLock, LW_EXCLUSIVE);

	pageno = MultiXactIdToOffsetPage(multi);
	entryno = MultiXactIdToOffsetEntry(multi);

	/*
	 * Note: we pass the MultiXactId to SimpleLruReadPage as the "transaction"
	 * to complain about if there's any I/O error.  This is kinda bogus, but
	 * since the errors will always give the full pathname, it should be clear
	 * enough that a MultiXactId is really involved.  Perhaps someday we'll
	 * take the trouble to generalize the slru.c error reporting code.
	 */
	slotno = SimpleLruReadPage(MultiXactOffsetCtl, pageno, true, multi);
	offptr = (MultiXactOffset *) MultiXactOffsetCtl->shared->page_buffer[slotno];
	offptr += entryno;

	*offptr = offset;

	MultiXactOffsetCtl->shared->page_dirty[slotno] = true;

	/* Exchange our lock */
	LWLockRelease(MultiXactOffsetControlLock);

	LWLockAcquire(MultiXactMemberControlLock, LW_EXCLUSIVE);

	prev_pageno = -1;

	for (i = 0; i < nmembers; i++, offset++)
	{
		TransactionId *memberptr;
		uint32	   *flagsptr;
		uint32		flagsval;
		int			bshift;
		int			flagsoff;
		int			memberoff;

		Assert(members[i].status <= MultiXactStatusUpdate);

		pageno = MXOffsetToMemberPage(offset);
		memberoff = MXOffsetToMemberOffset(offset);
		flagsoff = MXOffsetToFlagsOffset(offset);
		bshift = MXOffsetToFlagsBitShift(offset);

		if (pageno != prev_pageno)
		{
			slotno = SimpleLruReadPage(MultiXactMemberCtl, pageno, true, multi);
			prev_pageno = pageno;
		}

		memberptr = (TransactionId *)
			(MultiXactMemberCtl->shared->page_buffer[slotno] + memberoff);

		*memberptr = members[i].xid;

		flagsptr = (uint32 *)
			(MultiXactMemberCtl->shared->page_buffer[slotno] + flagsoff);

		flagsval = *flagsptr;
		flagsval &= ~(((1 << MXACT_MEMBER_BITS_PER_XACT) - 1) << bshift);
		flagsval |= (members[i].status << bshift);
		*flagsptr = flagsval;

		MultiXactMemberCtl->shared->page_dirty[slotno] = true;
	}

	LWLockRelease(MultiXactMemberControlLock);
}