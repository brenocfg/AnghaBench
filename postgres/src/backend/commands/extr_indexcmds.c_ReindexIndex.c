#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ReindexIndexCallbackState {int concurrent; int /*<<< orphan*/  locked_table_oid; } ;
struct TYPE_7__ {TYPE_1__* rd_rel; } ;
struct TYPE_6__ {scalar_t__ relkind; char relpersistence; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NoLock ; 
 int REINDEXOPT_REPORT_PROGRESS ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  RangeVarCallbackForReindexIndex ; 
 int /*<<< orphan*/  RangeVarGetRelidExtended (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ReindexIndexCallbackState*) ; 
 int /*<<< orphan*/  ReindexPartitionedIndex (TYPE_2__*) ; 
 int /*<<< orphan*/  ReindexRelationConcurrently (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  index_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reindex_index (int /*<<< orphan*/ ,int,char,int) ; 

void
ReindexIndex(RangeVar *indexRelation, int options, bool concurrent)
{
	struct ReindexIndexCallbackState state;
	Oid			indOid;
	Relation	irel;
	char		persistence;

	/*
	 * Find and lock index, and check permissions on table; use callback to
	 * obtain lock on table first, to avoid deadlock hazard.  The lock level
	 * used here must match the index lock obtained in reindex_index().
	 */
	state.concurrent = concurrent;
	state.locked_table_oid = InvalidOid;
	indOid = RangeVarGetRelidExtended(indexRelation,
									  concurrent ? ShareUpdateExclusiveLock : AccessExclusiveLock,
									  0,
									  RangeVarCallbackForReindexIndex,
									  &state);

	/*
	 * Obtain the current persistence of the existing index.  We already hold
	 * lock on the index.
	 */
	irel = index_open(indOid, NoLock);

	if (irel->rd_rel->relkind == RELKIND_PARTITIONED_INDEX)
	{
		ReindexPartitionedIndex(irel);
		return;
	}

	persistence = irel->rd_rel->relpersistence;
	index_close(irel, NoLock);

	if (concurrent)
		ReindexRelationConcurrently(indOid, options);
	else
		reindex_index(indOid, false, persistence,
					  options | REINDEXOPT_REPORT_PROGRESS);
}