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
struct TYPE_4__ {scalar_t__ toplevel_xid; scalar_t__ xid; scalar_t__ base_snapshot_lsn; int /*<<< orphan*/ * base_snapshot; int /*<<< orphan*/  base_snapshot_node; } ;
typedef  TYPE_1__ ReorderBufferTXN ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 void* InvalidXLogRecPtr ; 
 int /*<<< orphan*/  SnapBuildSnapDecRefcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ReorderBufferTransferSnapToParent(ReorderBufferTXN *txn,
								  ReorderBufferTXN *subtxn)
{
	Assert(subtxn->toplevel_xid == txn->xid);

	if (subtxn->base_snapshot != NULL)
	{
		if (txn->base_snapshot == NULL ||
			subtxn->base_snapshot_lsn < txn->base_snapshot_lsn)
		{
			/*
			 * If the toplevel transaction already has a base snapshot but
			 * it's newer than the subxact's, purge it.
			 */
			if (txn->base_snapshot != NULL)
			{
				SnapBuildSnapDecRefcount(txn->base_snapshot);
				dlist_delete(&txn->base_snapshot_node);
			}

			/*
			 * The snapshot is now the top transaction's; transfer it, and
			 * adjust the list position of the top transaction in the list by
			 * moving it to where the subtransaction is.
			 */
			txn->base_snapshot = subtxn->base_snapshot;
			txn->base_snapshot_lsn = subtxn->base_snapshot_lsn;
			dlist_insert_before(&subtxn->base_snapshot_node,
								&txn->base_snapshot_node);

			/*
			 * The subtransaction doesn't have a snapshot anymore (so it
			 * mustn't be in the list.)
			 */
			subtxn->base_snapshot = NULL;
			subtxn->base_snapshot_lsn = InvalidXLogRecPtr;
			dlist_delete(&subtxn->base_snapshot_node);
		}
		else
		{
			/* Base snap of toplevel is fine, so subxact's is not needed */
			SnapBuildSnapDecRefcount(subtxn->base_snapshot);
			dlist_delete(&subtxn->base_snapshot_node);
			subtxn->base_snapshot = NULL;
			subtxn->base_snapshot_lsn = InvalidXLogRecPtr;
		}
	}
}