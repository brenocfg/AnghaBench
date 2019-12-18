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
struct TYPE_2__ {int headPage; int /*<<< orphan*/  tailXid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  OldSerXidLock ; 
 int OldSerXidPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OldSerXidSlruCtl ; 
 int /*<<< orphan*/  SimpleLruFlush (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SimpleLruTruncate (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 TYPE_1__* oldSerXidControl ; 

void
CheckPointPredicate(void)
{
	int			tailPage;

	LWLockAcquire(OldSerXidLock, LW_EXCLUSIVE);

	/* Exit quickly if the SLRU is currently not in use. */
	if (oldSerXidControl->headPage < 0)
	{
		LWLockRelease(OldSerXidLock);
		return;
	}

	if (TransactionIdIsValid(oldSerXidControl->tailXid))
	{
		/* We can truncate the SLRU up to the page containing tailXid */
		tailPage = OldSerXidPage(oldSerXidControl->tailXid);
	}
	else
	{
		/*
		 * The SLRU is no longer needed. Truncate to head before we set head
		 * invalid.
		 *
		 * XXX: It's possible that the SLRU is not needed again until XID
		 * wrap-around has happened, so that the segment containing headPage
		 * that we leave behind will appear to be new again. In that case it
		 * won't be removed until XID horizon advances enough to make it
		 * current again.
		 */
		tailPage = oldSerXidControl->headPage;
		oldSerXidControl->headPage = -1;
	}

	LWLockRelease(OldSerXidLock);

	/* Truncate away pages that are no longer required */
	SimpleLruTruncate(OldSerXidSlruCtl, tailPage);

	/*
	 * Flush dirty SLRU pages to disk
	 *
	 * This is not actually necessary from a correctness point of view. We do
	 * it merely as a debugging aid.
	 *
	 * We're doing this after the truncation to avoid writing pages right
	 * before deleting the file in which they sit, which would be completely
	 * pointless.
	 */
	SimpleLruFlush(OldSerXidSlruCtl, true);
}