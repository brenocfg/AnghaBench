#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_5__ {int /*<<< orphan*/  snapshot; } ;
struct TYPE_6__ {int /*<<< orphan*/  action; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__ ReorderBufferChange ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  REORDER_BUFFER_CHANGE_INTERNAL_SNAPSHOT ; 
 TYPE_2__* ReorderBufferGetChange (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReorderBufferQueueChange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

void
ReorderBufferAddSnapshot(ReorderBuffer *rb, TransactionId xid,
						 XLogRecPtr lsn, Snapshot snap)
{
	ReorderBufferChange *change = ReorderBufferGetChange(rb);

	change->data.snapshot = snap;
	change->action = REORDER_BUFFER_CHANGE_INTERNAL_SNAPSHOT;

	ReorderBufferQueueChange(rb, xid, lsn, change);
}