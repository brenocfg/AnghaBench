#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_6__ {int rs_nkeys; int rs_flags; int /*<<< orphan*/ * rs_key; int /*<<< orphan*/  rs_parallel; scalar_t__ rs_snapshot; int /*<<< orphan*/  rs_rd; } ;
struct TYPE_5__ {int /*<<< orphan*/  t_tableOid; } ;
struct TYPE_7__ {TYPE_2__ rs_base; TYPE_1__ rs_ctup; int /*<<< orphan*/ * rs_strategy; } ;
typedef  scalar_t__ Snapshot ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * ScanKey ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ParallelTableScanDesc ;
typedef  int /*<<< orphan*/  HeapScanDescData ;
typedef  TYPE_3__* HeapScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 scalar_t__ IsMVCCSnapshot (scalar_t__) ; 
 int /*<<< orphan*/  PredicateLockRelation (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationIncrementReferenceCount (int /*<<< orphan*/ ) ; 
 int SO_ALLOW_PAGEMODE ; 
 int SO_TYPE_SAMPLESCAN ; 
 int SO_TYPE_SEQSCAN ; 
 int /*<<< orphan*/  initscan (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc (int) ; 

TableScanDesc
heap_beginscan(Relation relation, Snapshot snapshot,
			   int nkeys, ScanKey key,
			   ParallelTableScanDesc parallel_scan,
			   uint32 flags)
{
	HeapScanDesc scan;

	/*
	 * increment relation ref count while scanning relation
	 *
	 * This is just to make really sure the relcache entry won't go away while
	 * the scan has a pointer to it.  Caller should be holding the rel open
	 * anyway, so this is redundant in all normal scenarios...
	 */
	RelationIncrementReferenceCount(relation);

	/*
	 * allocate and initialize scan descriptor
	 */
	scan = (HeapScanDesc) palloc(sizeof(HeapScanDescData));

	scan->rs_base.rs_rd = relation;
	scan->rs_base.rs_snapshot = snapshot;
	scan->rs_base.rs_nkeys = nkeys;
	scan->rs_base.rs_flags = flags;
	scan->rs_base.rs_parallel = parallel_scan;
	scan->rs_strategy = NULL;	/* set in initscan */

	/*
	 * Disable page-at-a-time mode if it's not a MVCC-safe snapshot.
	 */
	if (!(snapshot && IsMVCCSnapshot(snapshot)))
		scan->rs_base.rs_flags &= ~SO_ALLOW_PAGEMODE;

	/*
	 * For seqscan and sample scans in a serializable transaction, acquire a
	 * predicate lock on the entire relation. This is required not only to
	 * lock all the matching tuples, but also to conflict with new insertions
	 * into the table. In an indexscan, we take page locks on the index pages
	 * covering the range specified in the scan qual, but in a heap scan there
	 * is nothing more fine-grained to lock. A bitmap scan is a different
	 * story, there we have already scanned the index and locked the index
	 * pages covering the predicate. But in that case we still have to lock
	 * any matching heap tuples. For sample scan we could optimize the locking
	 * to be at least page-level granularity, but we'd need to add per-tuple
	 * locking for that.
	 */
	if (scan->rs_base.rs_flags & (SO_TYPE_SEQSCAN | SO_TYPE_SAMPLESCAN))
	{
		/*
		 * Ensure a missing snapshot is noticed reliably, even if the
		 * isolation mode means predicate locking isn't performed (and
		 * therefore the snapshot isn't used here).
		 */
		Assert(snapshot);
		PredicateLockRelation(relation, snapshot);
	}

	/* we only need to set this up once */
	scan->rs_ctup.t_tableOid = RelationGetRelid(relation);

	/*
	 * we do this here instead of in initscan() because heap_rescan also calls
	 * initscan() and we don't want to allocate memory again
	 */
	if (nkeys > 0)
		scan->rs_base.rs_key = (ScanKey) palloc(sizeof(ScanKeyData) * nkeys);
	else
		scan->rs_base.rs_key = NULL;

	initscan(scan, key, false);

	return (TableScanDesc) scan;
}