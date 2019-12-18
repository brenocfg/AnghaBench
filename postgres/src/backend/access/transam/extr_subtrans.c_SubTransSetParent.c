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
typedef  scalar_t__ TransactionId ;
struct TYPE_5__ {TYPE_1__* shared; } ;
struct TYPE_4__ {int* page_dirty; scalar_t__* page_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int SimpleLruReadPage (TYPE_2__*,int,int,scalar_t__) ; 
 TYPE_2__* SubTransCtl ; 
 int /*<<< orphan*/  SubtransControlLock ; 
 int TransactionIdFollows (scalar_t__,scalar_t__) ; 
 int TransactionIdIsValid (scalar_t__) ; 
 int TransactionIdToEntry (scalar_t__) ; 
 int TransactionIdToPage (scalar_t__) ; 

void
SubTransSetParent(TransactionId xid, TransactionId parent)
{
	int			pageno = TransactionIdToPage(xid);
	int			entryno = TransactionIdToEntry(xid);
	int			slotno;
	TransactionId *ptr;

	Assert(TransactionIdIsValid(parent));
	Assert(TransactionIdFollows(xid, parent));

	LWLockAcquire(SubtransControlLock, LW_EXCLUSIVE);

	slotno = SimpleLruReadPage(SubTransCtl, pageno, true, xid);
	ptr = (TransactionId *) SubTransCtl->shared->page_buffer[slotno];
	ptr += entryno;

	/*
	 * It's possible we'll try to set the parent xid multiple times but we
	 * shouldn't ever be changing the xid from one valid xid to another valid
	 * xid, which would corrupt the data structure.
	 */
	if (*ptr != parent)
	{
		Assert(*ptr == InvalidTransactionId);
		*ptr = parent;
		SubTransCtl->shared->page_dirty[slotno] = true;
	}

	LWLockRelease(SubtransControlLock);
}