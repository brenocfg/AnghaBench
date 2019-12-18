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
struct TYPE_2__ {int indislive; int indisready; int indisvalid; int indisclustered; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int IndexStateFlagsAction ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ GetTopTransactionIdIfAny () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
#define  INDEX_CREATE_SET_READY 131 
#define  INDEX_CREATE_SET_VALID 130 
#define  INDEX_DROP_CLEAR_VALID 129 
#define  INDEX_DROP_SET_DEAD 128 
 int /*<<< orphan*/  IndexRelationId ; 
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_inplace_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
index_set_state_flags(Oid indexId, IndexStateFlagsAction action)
{
	Relation	pg_index;
	HeapTuple	indexTuple;
	Form_pg_index indexForm;

	/* Assert that current xact hasn't done any transactional updates */
	Assert(GetTopTransactionIdIfAny() == InvalidTransactionId);

	/* Open pg_index and fetch a writable copy of the index's tuple */
	pg_index = table_open(IndexRelationId, RowExclusiveLock);

	indexTuple = SearchSysCacheCopy1(INDEXRELID,
									 ObjectIdGetDatum(indexId));
	if (!HeapTupleIsValid(indexTuple))
		elog(ERROR, "cache lookup failed for index %u", indexId);
	indexForm = (Form_pg_index) GETSTRUCT(indexTuple);

	/* Perform the requested state change on the copy */
	switch (action)
	{
		case INDEX_CREATE_SET_READY:
			/* Set indisready during a CREATE INDEX CONCURRENTLY sequence */
			Assert(indexForm->indislive);
			Assert(!indexForm->indisready);
			Assert(!indexForm->indisvalid);
			indexForm->indisready = true;
			break;
		case INDEX_CREATE_SET_VALID:
			/* Set indisvalid during a CREATE INDEX CONCURRENTLY sequence */
			Assert(indexForm->indislive);
			Assert(indexForm->indisready);
			Assert(!indexForm->indisvalid);
			indexForm->indisvalid = true;
			break;
		case INDEX_DROP_CLEAR_VALID:

			/*
			 * Clear indisvalid during a DROP INDEX CONCURRENTLY sequence
			 *
			 * If indisready == true we leave it set so the index still gets
			 * maintained by active transactions.  We only need to ensure that
			 * indisvalid is false.  (We don't assert that either is initially
			 * true, though, since we want to be able to retry a DROP INDEX
			 * CONCURRENTLY that failed partway through.)
			 *
			 * Note: the CLUSTER logic assumes that indisclustered cannot be
			 * set on any invalid index, so clear that flag too.
			 */
			indexForm->indisvalid = false;
			indexForm->indisclustered = false;
			break;
		case INDEX_DROP_SET_DEAD:

			/*
			 * Clear indisready/indislive during DROP INDEX CONCURRENTLY
			 *
			 * We clear both indisready and indislive, because we not only
			 * want to stop updates, we want to prevent sessions from touching
			 * the index at all.
			 */
			Assert(!indexForm->indisvalid);
			indexForm->indisready = false;
			indexForm->indislive = false;
			break;
	}

	/* ... and write it back in-place */
	heap_inplace_update(pg_index, indexTuple);

	table_close(pg_index, RowExclusiveLock);
}