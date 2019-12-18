#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ii_Concurrent; int ii_BrokenHotChain; int /*<<< orphan*/  ii_ReadyForInserts; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ IndexInfo ;

/* Variables and functions */
 int ActiveSnapshotSet () ; 
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* BuildIndexInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEX_CREATE_SET_READY ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  index_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  index_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_set_state_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
index_concurrently_build(Oid heapRelationId,
						 Oid indexRelationId)
{
	Relation	heapRel;
	Relation	indexRelation;
	IndexInfo  *indexInfo;

	/* This had better make sure that a snapshot is active */
	Assert(ActiveSnapshotSet());

	/* Open and lock the parent heap relation */
	heapRel = table_open(heapRelationId, ShareUpdateExclusiveLock);

	/* And the target index relation */
	indexRelation = index_open(indexRelationId, RowExclusiveLock);

	/*
	 * We have to re-build the IndexInfo struct, since it was lost in the
	 * commit of the transaction where this concurrent index was created at
	 * the catalog level.
	 */
	indexInfo = BuildIndexInfo(indexRelation);
	Assert(!indexInfo->ii_ReadyForInserts);
	indexInfo->ii_Concurrent = true;
	indexInfo->ii_BrokenHotChain = false;

	/* Now build the index */
	index_build(heapRel, indexRelation, indexInfo, false, true);

	/* Close both the relations, but keep the locks */
	table_close(heapRel, NoLock);
	index_close(indexRelation, NoLock);

	/*
	 * Update the pg_index row to mark the index as ready for inserts. Once we
	 * commit this transaction, any new transactions that open the table must
	 * insert new entries into the index for insertions and non-HOT updates.
	 */
	index_set_state_flags(indexRelationId, INDEX_CREATE_SET_READY);
}