#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_19__ {scalar_t__ t_len; int /*<<< orphan*/  t_tableOid; TYPE_11__* t_data; } ;
struct TYPE_18__ {TYPE_1__* rd_rel; } ;
struct TYPE_17__ {scalar_t__ relkind; } ;
struct TYPE_16__ {int /*<<< orphan*/  t_infomask; int /*<<< orphan*/  t_infomask2; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* HeapTuple ;
typedef  int /*<<< orphan*/  CommandId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TRANSACTION_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HEAP2_XACT_MASK ; 
 int HEAP_INSERT_FROZEN ; 
 int /*<<< orphan*/  HEAP_XACT_MASK ; 
 int /*<<< orphan*/  HEAP_XMAX_INVALID ; 
 scalar_t__ HeapTupleHasExternal (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetCmin (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmax (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmin (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXminFrozen (TYPE_11__*) ; 
 scalar_t__ IsParallelWorker () ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 scalar_t__ TOAST_TUPLE_THRESHOLD ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_3__* heap_toast_insert_or_update (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HeapTuple
heap_prepare_insert(Relation relation, HeapTuple tup, TransactionId xid,
					CommandId cid, int options)
{
	/*
	 * Parallel operations are required to be strictly read-only in a parallel
	 * worker.  Parallel inserts are not safe even in the leader in the
	 * general case, because group locking means that heavyweight locks for
	 * relation extension or GIN page locks will not conflict between members
	 * of a lock group, but we don't prohibit that case here because there are
	 * useful special cases that we can safely allow, such as CREATE TABLE AS.
	 */
	if (IsParallelWorker())
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TRANSACTION_STATE),
				 errmsg("cannot insert tuples in a parallel worker")));

	tup->t_data->t_infomask &= ~(HEAP_XACT_MASK);
	tup->t_data->t_infomask2 &= ~(HEAP2_XACT_MASK);
	tup->t_data->t_infomask |= HEAP_XMAX_INVALID;
	HeapTupleHeaderSetXmin(tup->t_data, xid);
	if (options & HEAP_INSERT_FROZEN)
		HeapTupleHeaderSetXminFrozen(tup->t_data);

	HeapTupleHeaderSetCmin(tup->t_data, cid);
	HeapTupleHeaderSetXmax(tup->t_data, 0); /* for cleanliness */
	tup->t_tableOid = RelationGetRelid(relation);

	/*
	 * If the new tuple is too big for storage or contains already toasted
	 * out-of-line attributes from some other relation, invoke the toaster.
	 */
	if (relation->rd_rel->relkind != RELKIND_RELATION &&
		relation->rd_rel->relkind != RELKIND_MATVIEW)
	{
		/* toast table entries should never be recursively toasted */
		Assert(!HeapTupleHasExternal(tup));
		return tup;
	}
	else if (HeapTupleHasExternal(tup) || tup->t_len > TOAST_TUPLE_THRESHOLD)
		return heap_toast_insert_or_update(relation, tup, NULL, options);
	else
		return tup;
}