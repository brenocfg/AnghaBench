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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {scalar_t__ ninvalidations; int /*<<< orphan*/  invalidations; int /*<<< orphan*/ * base_snapshot; int /*<<< orphan*/  final_lsn; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  ReorderBufferCleanupTXN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ReorderBufferImmediateInvalidation (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* ReorderBufferTXNByXid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
ReorderBufferForget(ReorderBuffer *rb, TransactionId xid, XLogRecPtr lsn)
{
	ReorderBufferTXN *txn;

	txn = ReorderBufferTXNByXid(rb, xid, false, NULL, InvalidXLogRecPtr,
								false);

	/* unknown, nothing to forget */
	if (txn == NULL)
		return;

	/* cosmetic... */
	txn->final_lsn = lsn;

	/*
	 * Process cache invalidation messages if there are any. Even if we're not
	 * interested in the transaction's contents, it could have manipulated the
	 * catalog and we need to update the caches according to that.
	 */
	if (txn->base_snapshot != NULL && txn->ninvalidations > 0)
		ReorderBufferImmediateInvalidation(rb, txn->ninvalidations,
										   txn->invalidations);
	else
		Assert(txn->ninvalidations == 0);

	/* remove potential on-disk data, and deallocate */
	ReorderBufferCleanupTXN(rb, txn);
}