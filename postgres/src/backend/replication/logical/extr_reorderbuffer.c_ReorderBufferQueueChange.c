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
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {int /*<<< orphan*/  node; scalar_t__ lsn; } ;
struct TYPE_6__ {int /*<<< orphan*/  nentries_mem; int /*<<< orphan*/  nentries; int /*<<< orphan*/  changes; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  TYPE_2__ ReorderBufferChange ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  ReorderBufferCheckSerializeTXN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ReorderBufferTXNByXid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  dlist_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ReorderBufferQueueChange(ReorderBuffer *rb, TransactionId xid, XLogRecPtr lsn,
						 ReorderBufferChange *change)
{
	ReorderBufferTXN *txn;

	txn = ReorderBufferTXNByXid(rb, xid, true, NULL, lsn, true);

	change->lsn = lsn;
	Assert(InvalidXLogRecPtr != lsn);
	dlist_push_tail(&txn->changes, &change->node);
	txn->nentries++;
	txn->nentries_mem++;

	ReorderBufferCheckSerializeTXN(rb, txn);
}