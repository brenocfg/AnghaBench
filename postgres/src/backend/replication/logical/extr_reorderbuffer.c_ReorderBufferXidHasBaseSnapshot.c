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
struct TYPE_3__ {int /*<<< orphan*/ * base_snapshot; int /*<<< orphan*/  toplevel_xid; scalar_t__ is_known_as_subxact; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 TYPE_1__* ReorderBufferTXNByXid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool
ReorderBufferXidHasBaseSnapshot(ReorderBuffer *rb, TransactionId xid)
{
	ReorderBufferTXN *txn;

	txn = ReorderBufferTXNByXid(rb, xid, false,
								NULL, InvalidXLogRecPtr, false);

	/* transaction isn't known yet, ergo no snapshot */
	if (txn == NULL)
		return false;

	/* a known subtxn? operate on top-level txn instead */
	if (txn->is_known_as_subxact)
		txn = ReorderBufferTXNByXid(rb, txn->toplevel_xid, false,
									NULL, InvalidXLogRecPtr, false);

	return txn->base_snapshot != NULL;
}