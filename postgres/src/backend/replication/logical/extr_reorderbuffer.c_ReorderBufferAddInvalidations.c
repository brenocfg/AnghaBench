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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {int /*<<< orphan*/  context; } ;
struct TYPE_6__ {scalar_t__ ninvalidations; int /*<<< orphan*/ * invalidations; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  TYPE_2__ ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ReorderBufferTXNByXid (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
ReorderBufferAddInvalidations(ReorderBuffer *rb, TransactionId xid,
							  XLogRecPtr lsn, Size nmsgs,
							  SharedInvalidationMessage *msgs)
{
	ReorderBufferTXN *txn;

	txn = ReorderBufferTXNByXid(rb, xid, true, NULL, lsn, true);

	if (txn->ninvalidations != 0)
		elog(ERROR, "only ever add one set of invalidations");

	Assert(nmsgs > 0);

	txn->ninvalidations = nmsgs;
	txn->invalidations = (SharedInvalidationMessage *)
		MemoryContextAlloc(rb->context,
						   sizeof(SharedInvalidationMessage) * nmsgs);
	memcpy(txn->invalidations, msgs,
		   sizeof(SharedInvalidationMessage) * nmsgs);
}