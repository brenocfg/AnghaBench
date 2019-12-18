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
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 scalar_t__ InvalidSerializableXact ; 
 int /*<<< orphan*/  IsMVCCSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ MySerializableXact ; 
 int /*<<< orphan*/  PredicateLockingNeededForRelation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleasePredicateLocks (int,int) ; 
 scalar_t__ SxactIsROSafe (scalar_t__) ; 

__attribute__((used)) static inline bool
SerializationNeededForRead(Relation relation, Snapshot snapshot)
{
	/* Nothing to do if this is not a serializable transaction */
	if (MySerializableXact == InvalidSerializableXact)
		return false;

	/*
	 * Don't acquire locks or conflict when scanning with a special snapshot.
	 * This excludes things like CLUSTER and REINDEX. They use the wholesale
	 * functions TransferPredicateLocksToHeapRelation() and
	 * CheckTableForSerializableConflictIn() to participate in serialization,
	 * but the scans involved don't need serialization.
	 */
	if (!IsMVCCSnapshot(snapshot))
		return false;

	/*
	 * Check if we have just become "RO-safe". If we have, immediately release
	 * all locks as they're not needed anymore. This also resets
	 * MySerializableXact, so that subsequent calls to this function can exit
	 * quickly.
	 *
	 * A transaction is flagged as RO_SAFE if all concurrent R/W transactions
	 * commit without having conflicts out to an earlier snapshot, thus
	 * ensuring that no conflicts are possible for this transaction.
	 */
	if (SxactIsROSafe(MySerializableXact))
	{
		ReleasePredicateLocks(false, true);
		return false;
	}

	/* Check if the relation doesn't participate in predicate locking */
	if (!PredicateLockingNeededForRelation(relation))
		return false;

	return true;				/* no excuse to skip predicate locking */
}