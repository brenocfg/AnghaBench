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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CacheInvalidateRelcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEX_DROP_SET_DEAD ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  TransferPredicateLocksToHeapRelation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_set_state_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
index_concurrently_set_dead(Oid heapId, Oid indexId)
{
	Relation	userHeapRelation;
	Relation	userIndexRelation;

	/*
	 * No more predicate locks will be acquired on this index, and we're about
	 * to stop doing inserts into the index which could show conflicts with
	 * existing predicate locks, so now is the time to move them to the heap
	 * relation.
	 */
	userHeapRelation = table_open(heapId, ShareUpdateExclusiveLock);
	userIndexRelation = index_open(indexId, ShareUpdateExclusiveLock);
	TransferPredicateLocksToHeapRelation(userIndexRelation);

	/*
	 * Now we are sure that nobody uses the index for queries; they just might
	 * have it open for updating it.  So now we can unset indisready and
	 * indislive, then wait till nobody could be using it at all anymore.
	 */
	index_set_state_flags(indexId, INDEX_DROP_SET_DEAD);

	/*
	 * Invalidate the relcache for the table, so that after this commit all
	 * sessions will refresh the table's index list.  Forgetting just the
	 * index's relcache entry is not enough.
	 */
	CacheInvalidateRelcache(userHeapRelation);

	/*
	 * Close the relations again, though still holding session lock.
	 */
	table_close(userHeapRelation, NoLock);
	index_close(userIndexRelation, NoLock);
}