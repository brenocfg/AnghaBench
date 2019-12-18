#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nsubxacts; int /*<<< orphan*/ * subxacts; } ;
typedef  TYPE_2__ xl_xact_parsed_abort ;
struct TYPE_10__ {TYPE_1__* record; } ;
typedef  TYPE_3__ XLogRecordBuffer ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_11__ {int /*<<< orphan*/  reorder; } ;
struct TYPE_8__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_4__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  ReorderBufferAbort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DecodeAbort(LogicalDecodingContext *ctx, XLogRecordBuffer *buf,
			xl_xact_parsed_abort *parsed, TransactionId xid)
{
	int			i;

	for (i = 0; i < parsed->nsubxacts; i++)
	{
		ReorderBufferAbort(ctx->reorder, parsed->subxacts[i],
						   buf->record->EndRecPtr);
	}

	ReorderBufferAbort(ctx->reorder, xid, buf->record->EndRecPtr);
}