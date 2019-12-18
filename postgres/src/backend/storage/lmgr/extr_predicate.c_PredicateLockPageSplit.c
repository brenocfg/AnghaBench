#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  SxactGlobalXmin; } ;
struct TYPE_6__ {int /*<<< orphan*/  dbNode; } ;
struct TYPE_7__ {int /*<<< orphan*/  rd_id; TYPE_1__ rd_node; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 int GetParentPredicateLockTag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_5__* PredXact ; 
 int /*<<< orphan*/  PredicateLockingNeededForRelation (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_PREDICATELOCKTARGETTAG_PAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SerializablePredicateLockListLock ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int TransferPredicateLocksToNewTarget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
PredicateLockPageSplit(Relation relation, BlockNumber oldblkno,
					   BlockNumber newblkno)
{
	PREDICATELOCKTARGETTAG oldtargettag;
	PREDICATELOCKTARGETTAG newtargettag;
	bool		success;

	/*
	 * Bail out quickly if there are no serializable transactions running.
	 *
	 * It's safe to do this check without taking any additional locks. Even if
	 * a serializable transaction starts concurrently, we know it can't take
	 * any SIREAD locks on the page being split because the caller is holding
	 * the associated buffer page lock. Memory reordering isn't an issue; the
	 * memory barrier in the LWLock acquisition guarantees that this read
	 * occurs while the buffer page lock is held.
	 */
	if (!TransactionIdIsValid(PredXact->SxactGlobalXmin))
		return;

	if (!PredicateLockingNeededForRelation(relation))
		return;

	Assert(oldblkno != newblkno);
	Assert(BlockNumberIsValid(oldblkno));
	Assert(BlockNumberIsValid(newblkno));

	SET_PREDICATELOCKTARGETTAG_PAGE(oldtargettag,
									relation->rd_node.dbNode,
									relation->rd_id,
									oldblkno);
	SET_PREDICATELOCKTARGETTAG_PAGE(newtargettag,
									relation->rd_node.dbNode,
									relation->rd_id,
									newblkno);

	LWLockAcquire(SerializablePredicateLockListLock, LW_EXCLUSIVE);

	/*
	 * Try copying the locks over to the new page's tag, creating it if
	 * necessary.
	 */
	success = TransferPredicateLocksToNewTarget(oldtargettag,
												newtargettag,
												false);

	if (!success)
	{
		/*
		 * No more predicate lock entries are available. Failure isn't an
		 * option here, so promote the page lock to a relation lock.
		 */

		/* Get the parent relation lock's lock tag */
		success = GetParentPredicateLockTag(&oldtargettag,
											&newtargettag);
		Assert(success);

		/*
		 * Move the locks to the parent. This shouldn't fail.
		 *
		 * Note that here we are removing locks held by other backends,
		 * leading to a possible inconsistency in their local lock hash table.
		 * This is OK because we're replacing it with a lock that covers the
		 * old one.
		 */
		success = TransferPredicateLocksToNewTarget(oldtargettag,
													newtargettag,
													true);
		Assert(success);
	}

	LWLockRelease(SerializablePredicateLockListLock);
}