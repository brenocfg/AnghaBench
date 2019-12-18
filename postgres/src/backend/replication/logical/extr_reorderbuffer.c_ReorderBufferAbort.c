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
struct TYPE_4__ {int /*<<< orphan*/  final_lsn; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  ReorderBufferCleanupTXN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ReorderBufferTXNByXid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
ReorderBufferAbort(ReorderBuffer *rb, TransactionId xid, XLogRecPtr lsn)
{
	ReorderBufferTXN *txn;

	txn = ReorderBufferTXNByXid(rb, xid, false, NULL, InvalidXLogRecPtr,
								false);

	/* unknown, nothing to remove */
	if (txn == NULL)
		return;

	/* cosmetic... */
	txn->final_lsn = lsn;

	/* remove potential on-disk data, and deallocate */
	ReorderBufferCleanupTXN(rb, txn);
}