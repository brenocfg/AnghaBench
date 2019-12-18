#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  XLogRecord ;
typedef  int XLogRecPtr ;
struct TYPE_12__ {int /*<<< orphan*/  EndRecPtr; } ;
struct TYPE_11__ {TYPE_4__* reader; TYPE_2__* slot; } ;
struct TYPE_9__ {int restart_lsn; int /*<<< orphan*/  confirmed_flush; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; TYPE_1__ data; } ;
typedef  TYPE_2__ ReplicationSlot ;
typedef  TYPE_3__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ DecodingContextReady (TYPE_3__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LogicalDecodingProcessRecord (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XLogReadRecord (TYPE_4__*,int,char**) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 

void
DecodingContextFindStartpoint(LogicalDecodingContext *ctx)
{
	XLogRecPtr	startptr;
	ReplicationSlot *slot = ctx->slot;

	/* Initialize from where to start reading WAL. */
	startptr = slot->data.restart_lsn;

	elog(DEBUG1, "searching for logical decoding starting point, starting at %X/%X",
		 (uint32) (slot->data.restart_lsn >> 32),
		 (uint32) slot->data.restart_lsn);

	/* Wait for a consistent starting point */
	for (;;)
	{
		XLogRecord *record;
		char	   *err = NULL;

		/* the read_page callback waits for new WAL */
		record = XLogReadRecord(ctx->reader, startptr, &err);
		if (err)
			elog(ERROR, "%s", err);
		if (!record)
			elog(ERROR, "no record found"); /* shouldn't happen */

		startptr = InvalidXLogRecPtr;

		LogicalDecodingProcessRecord(ctx, ctx->reader);

		/* only continue till we found a consistent spot */
		if (DecodingContextReady(ctx))
			break;

		CHECK_FOR_INTERRUPTS();
	}

	SpinLockAcquire(&slot->mutex);
	slot->data.confirmed_flush = ctx->reader->EndRecPtr;
	SpinLockRelease(&slot->mutex);
}