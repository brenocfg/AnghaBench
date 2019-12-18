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
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ LockAcquireResult ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptInvalidationMessages () ; 
 scalar_t__ LOCKACQUIRE_ALREADY_CLEAR ; 
 scalar_t__ LockAcquireExtended (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MarkLockClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLocktagRelationOid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
LockRelationOid(Oid relid, LOCKMODE lockmode)
{
	LOCKTAG		tag;
	LOCALLOCK  *locallock;
	LockAcquireResult res;

	SetLocktagRelationOid(&tag, relid);

	res = LockAcquireExtended(&tag, lockmode, false, false, true, &locallock);

	/*
	 * Now that we have the lock, check for invalidation messages, so that we
	 * will update or flush any stale relcache entry before we try to use it.
	 * RangeVarGetRelid() specifically relies on us for this.  We can skip
	 * this in the not-uncommon case that we already had the same type of lock
	 * being requested, since then no one else could have modified the
	 * relcache entry in an undesirable way.  (In the case where our own xact
	 * modifies the rel, the relcache update happens via
	 * CommandCounterIncrement, not here.)
	 *
	 * However, in corner cases where code acts on tables (usually catalogs)
	 * recursively, we might get here while still processing invalidation
	 * messages in some outer execution of this function or a sibling.  The
	 * "cleared" status of the lock tells us whether we really are done
	 * absorbing relevant inval messages.
	 */
	if (res != LOCKACQUIRE_ALREADY_CLEAR)
	{
		AcceptInvalidationMessages();
		MarkLockClear(locallock);
	}
}