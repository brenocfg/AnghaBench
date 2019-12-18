#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_3__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_data; } ;
typedef  int /*<<< orphan*/  TM_Result ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  LockTupleMode ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  HeapTupleHeaderIndicatesMovedPartitions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiXactIdSetOldestMember () ; 
 int /*<<< orphan*/  TM_Ok ; 
 int /*<<< orphan*/  heap_lock_updated_tuple_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TM_Result
heap_lock_updated_tuple(Relation rel, HeapTuple tuple, ItemPointer ctid,
						TransactionId xid, LockTupleMode mode)
{
	/*
	 * If the tuple has not been updated, or has moved into another partition
	 * (effectively a delete) stop here.
	 */
	if (!HeapTupleHeaderIndicatesMovedPartitions(tuple->t_data) &&
		!ItemPointerEquals(&tuple->t_self, ctid))
	{
		/*
		 * If this is the first possibly-multixact-able operation in the
		 * current transaction, set my per-backend OldestMemberMXactId
		 * setting. We can be certain that the transaction will never become a
		 * member of any older MultiXactIds than that.  (We have to do this
		 * even if we end up just using our own TransactionId below, since
		 * some other backend could incorporate our XID into a MultiXact
		 * immediately afterwards.)
		 */
		MultiXactIdSetOldestMember();

		return heap_lock_updated_tuple_rec(rel, ctid, xid, mode);
	}

	/* nothing to lock */
	return TM_Ok;
}