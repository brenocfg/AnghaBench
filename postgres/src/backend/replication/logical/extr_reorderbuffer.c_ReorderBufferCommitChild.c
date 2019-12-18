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
typedef  void* XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_3__ {void* end_lsn; void* final_lsn; } ;
typedef  TYPE_1__ ReorderBufferTXN ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  ReorderBufferAssignChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ReorderBufferTXNByXid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
ReorderBufferCommitChild(ReorderBuffer *rb, TransactionId xid,
						 TransactionId subxid, XLogRecPtr commit_lsn,
						 XLogRecPtr end_lsn)
{
	ReorderBufferTXN *subtxn;

	subtxn = ReorderBufferTXNByXid(rb, subxid, false, NULL,
								   InvalidXLogRecPtr, false);

	/*
	 * No need to do anything if that subtxn didn't contain any changes
	 */
	if (!subtxn)
		return;

	subtxn->final_lsn = commit_lsn;
	subtxn->end_lsn = end_lsn;

	/*
	 * Assign this subxact as a child of the toplevel xact (no-op if already
	 * done.)
	 */
	ReorderBufferAssignChild(rb, xid, subxid, InvalidXLogRecPtr);
}