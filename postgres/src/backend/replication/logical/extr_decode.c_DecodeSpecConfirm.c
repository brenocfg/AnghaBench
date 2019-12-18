#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  origptr; int /*<<< orphan*/ * record; } ;
typedef  TYPE_5__ XLogRecordBuffer ;
typedef  int /*<<< orphan*/  XLogReaderState ;
struct TYPE_23__ {int /*<<< orphan*/  reorder; TYPE_2__* slot; } ;
struct TYPE_22__ {scalar_t__ dbNode; } ;
struct TYPE_18__ {int clear_toast_afterwards; int /*<<< orphan*/  relnode; } ;
struct TYPE_19__ {TYPE_3__ tp; } ;
struct TYPE_21__ {TYPE_4__ data; int /*<<< orphan*/  origin_id; int /*<<< orphan*/  action; } ;
struct TYPE_16__ {scalar_t__ database; } ;
struct TYPE_17__ {TYPE_1__ data; } ;
typedef  TYPE_6__ ReorderBufferChange ;
typedef  TYPE_7__ RelFileNode ;
typedef  TYPE_8__ LogicalDecodingContext ;

/* Variables and functions */
 scalar_t__ FilterByOrigin (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REORDER_BUFFER_CHANGE_INTERNAL_SPEC_CONFIRM ; 
 TYPE_6__* ReorderBufferGetChange (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferQueueChange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetOrigin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetXid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_7__*,int) ; 

__attribute__((used)) static void
DecodeSpecConfirm(LogicalDecodingContext *ctx, XLogRecordBuffer *buf)
{
	XLogReaderState *r = buf->record;
	ReorderBufferChange *change;
	RelFileNode target_node;

	/* only interested in our database */
	XLogRecGetBlockTag(r, 0, &target_node, NULL, NULL);
	if (target_node.dbNode != ctx->slot->data.database)
		return;

	/* output plugin doesn't look for this origin, no need to queue */
	if (FilterByOrigin(ctx, XLogRecGetOrigin(r)))
		return;

	change = ReorderBufferGetChange(ctx->reorder);
	change->action = REORDER_BUFFER_CHANGE_INTERNAL_SPEC_CONFIRM;
	change->origin_id = XLogRecGetOrigin(r);

	memcpy(&change->data.tp.relnode, &target_node, sizeof(RelFileNode));

	change->data.tp.clear_toast_afterwards = true;

	ReorderBufferQueueChange(ctx->reorder, XLogRecGetXid(r), buf->origptr, change);
}