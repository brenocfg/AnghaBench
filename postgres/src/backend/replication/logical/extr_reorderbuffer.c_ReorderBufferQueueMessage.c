#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
struct TYPE_15__ {int /*<<< orphan*/  (* message ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,char const*) ;int /*<<< orphan*/  context; } ;
struct TYPE_12__ {int /*<<< orphan*/  message; int /*<<< orphan*/  message_size; int /*<<< orphan*/  prefix; } ;
struct TYPE_13__ {TYPE_1__ msg; } ;
struct TYPE_14__ {TYPE_2__ data; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  ReorderBufferTXN ;
typedef  TYPE_3__ ReorderBufferChange ;
typedef  TYPE_4__ ReorderBuffer ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  REORDER_BUFFER_CHANGE_MESSAGE ; 
 TYPE_3__* ReorderBufferGetChange (TYPE_4__*) ; 
 int /*<<< orphan*/  ReorderBufferQueueChange (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * ReorderBufferTXNByXid (TYPE_4__*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetupHistoricSnapshot (int /*<<< orphan*/  volatile,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TeardownHistoricSnapshot (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,char const*) ; 

void
ReorderBufferQueueMessage(ReorderBuffer *rb, TransactionId xid,
						  Snapshot snapshot, XLogRecPtr lsn,
						  bool transactional, const char *prefix,
						  Size message_size, const char *message)
{
	if (transactional)
	{
		MemoryContext oldcontext;
		ReorderBufferChange *change;

		Assert(xid != InvalidTransactionId);

		oldcontext = MemoryContextSwitchTo(rb->context);

		change = ReorderBufferGetChange(rb);
		change->action = REORDER_BUFFER_CHANGE_MESSAGE;
		change->data.msg.prefix = pstrdup(prefix);
		change->data.msg.message_size = message_size;
		change->data.msg.message = palloc(message_size);
		memcpy(change->data.msg.message, message, message_size);

		ReorderBufferQueueChange(rb, xid, lsn, change);

		MemoryContextSwitchTo(oldcontext);
	}
	else
	{
		ReorderBufferTXN *txn = NULL;
		volatile Snapshot snapshot_now = snapshot;

		if (xid != InvalidTransactionId)
			txn = ReorderBufferTXNByXid(rb, xid, true, NULL, lsn, true);

		/* setup snapshot to allow catalog access */
		SetupHistoricSnapshot(snapshot_now, NULL);
		PG_TRY();
		{
			rb->message(rb, txn, lsn, false, prefix, message_size, message);

			TeardownHistoricSnapshot(false);
		}
		PG_CATCH();
		{
			TeardownHistoricSnapshot(true);
			PG_RE_THROW();
		}
		PG_END_TRY();
	}
}