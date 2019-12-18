#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_8__ {int /*<<< orphan*/  txns_by_base_snapshot_lsn; } ;
struct TYPE_7__ {int /*<<< orphan*/  base_snapshot_node; int /*<<< orphan*/  base_snapshot_lsn; int /*<<< orphan*/ * base_snapshot; int /*<<< orphan*/  toplevel_xid; scalar_t__ is_known_as_subxact; } ;
typedef  int /*<<< orphan*/ * Snapshot ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  TYPE_2__ ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AssertTXNLsnOrder (TYPE_2__*) ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 TYPE_1__* ReorderBufferTXNByXid (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dlist_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ReorderBufferSetBaseSnapshot(ReorderBuffer *rb, TransactionId xid,
							 XLogRecPtr lsn, Snapshot snap)
{
	ReorderBufferTXN *txn;
	bool		is_new;

	AssertArg(snap != NULL);

	/*
	 * Fetch the transaction to operate on.  If we know it's a subtransaction,
	 * operate on its top-level transaction instead.
	 */
	txn = ReorderBufferTXNByXid(rb, xid, true, &is_new, lsn, true);
	if (txn->is_known_as_subxact)
		txn = ReorderBufferTXNByXid(rb, txn->toplevel_xid, false,
									NULL, InvalidXLogRecPtr, false);
	Assert(txn->base_snapshot == NULL);

	txn->base_snapshot = snap;
	txn->base_snapshot_lsn = lsn;
	dlist_push_tail(&rb->txns_by_base_snapshot_lsn, &txn->base_snapshot_node);

	AssertTXNLsnOrder(rb);
}