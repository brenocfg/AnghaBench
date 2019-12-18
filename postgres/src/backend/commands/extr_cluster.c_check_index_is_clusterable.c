#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* rd_index; int /*<<< orphan*/  rd_indextuple; TYPE_1__* rd_indam; } ;
struct TYPE_10__ {scalar_t__ indrelid; int /*<<< orphan*/  indisvalid; } ;
struct TYPE_9__ {int /*<<< orphan*/  amclusterable; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_index_indpred ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 scalar_t__ RelationGetRelid (TYPE_3__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  heap_attisnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
check_index_is_clusterable(Relation OldHeap, Oid indexOid, bool recheck, LOCKMODE lockmode)
{
	Relation	OldIndex;

	OldIndex = index_open(indexOid, lockmode);

	/*
	 * Check that index is in fact an index on the given relation
	 */
	if (OldIndex->rd_index == NULL ||
		OldIndex->rd_index->indrelid != RelationGetRelid(OldHeap))
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("\"%s\" is not an index for table \"%s\"",
						RelationGetRelationName(OldIndex),
						RelationGetRelationName(OldHeap))));

	/* Index AM must allow clustering */
	if (!OldIndex->rd_indam->amclusterable)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot cluster on index \"%s\" because access method does not support clustering",
						RelationGetRelationName(OldIndex))));

	/*
	 * Disallow clustering on incomplete indexes (those that might not index
	 * every row of the relation).  We could relax this by making a separate
	 * seqscan pass over the table to copy the missing rows, but that seems
	 * expensive and tedious.
	 */
	if (!heap_attisnull(OldIndex->rd_indextuple, Anum_pg_index_indpred, NULL))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot cluster on partial index \"%s\"",
						RelationGetRelationName(OldIndex))));

	/*
	 * Disallow if index is left over from a failed CREATE INDEX CONCURRENTLY;
	 * it might well not contain entries for every heap row, or might not even
	 * be internally consistent.  (But note that we don't check indcheckxmin;
	 * the worst consequence of following broken HOT chains would be that we
	 * might put recently-dead tuples out-of-order in the new table, and there
	 * is little harm in that.)
	 */
	if (!OldIndex->rd_index->indisvalid)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot cluster on invalid index \"%s\"",
						RelationGetRelationName(OldIndex))));

	/* Drop relcache refcnt on OldIndex, but keep lock */
	index_close(OldIndex, NoLock);
}