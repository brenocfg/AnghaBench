#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {void* combocid; void* cmax; void* cmin; int /*<<< orphan*/  tid; int /*<<< orphan*/  node; } ;
struct TYPE_8__ {TYPE_1__ tuplecid; } ;
struct TYPE_10__ {int /*<<< orphan*/  node; int /*<<< orphan*/  action; int /*<<< orphan*/  lsn; TYPE_2__ data; } ;
struct TYPE_9__ {int /*<<< orphan*/  ntuplecids; int /*<<< orphan*/  tuplecids; } ;
typedef  TYPE_3__ ReorderBufferTXN ;
typedef  TYPE_4__ ReorderBufferChange ;
typedef  int /*<<< orphan*/  ReorderBuffer ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  void* CommandId ;

/* Variables and functions */
 int /*<<< orphan*/  REORDER_BUFFER_CHANGE_INTERNAL_TUPLECID ; 
 TYPE_4__* ReorderBufferGetChange (int /*<<< orphan*/ *) ; 
 TYPE_3__* ReorderBufferTXNByXid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dlist_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ReorderBufferAddNewTupleCids(ReorderBuffer *rb, TransactionId xid,
							 XLogRecPtr lsn, RelFileNode node,
							 ItemPointerData tid, CommandId cmin,
							 CommandId cmax, CommandId combocid)
{
	ReorderBufferChange *change = ReorderBufferGetChange(rb);
	ReorderBufferTXN *txn;

	txn = ReorderBufferTXNByXid(rb, xid, true, NULL, lsn, true);

	change->data.tuplecid.node = node;
	change->data.tuplecid.tid = tid;
	change->data.tuplecid.cmin = cmin;
	change->data.tuplecid.cmax = cmax;
	change->data.tuplecid.combocid = combocid;
	change->lsn = lsn;
	change->action = REORDER_BUFFER_CHANGE_INTERNAL_TUPLECID;

	dlist_push_tail(&txn->tuplecids, &change->node);
	txn->ntuplecids++;
}