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
struct TYPE_5__ {scalar_t__* max_pending; scalar_t__ nr_pending; TYPE_2__* pending_writebacks; } ;
typedef  TYPE_1__ WritebackContext ;
struct TYPE_6__ {int /*<<< orphan*/  tag; } ;
typedef  TYPE_2__ PendingWriteback ;
typedef  int /*<<< orphan*/  BufferTag ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  IssuePendingWritebacks (TYPE_1__*) ; 
 scalar_t__ WRITEBACK_MAX_PENDING_FLUSHES ; 

void
ScheduleBufferTagForWriteback(WritebackContext *context, BufferTag *tag)
{
	PendingWriteback *pending;

	/*
	 * Add buffer to the pending writeback array, unless writeback control is
	 * disabled.
	 */
	if (*context->max_pending > 0)
	{
		Assert(*context->max_pending <= WRITEBACK_MAX_PENDING_FLUSHES);

		pending = &context->pending_writebacks[context->nr_pending++];

		pending->tag = *tag;
	}

	/*
	 * Perform pending flushes if the writeback limit is exceeded. This
	 * includes the case where previously an item has been added, but control
	 * is now disabled.
	 */
	if (context->nr_pending >= *context->max_pending)
		IssuePendingWritebacks(context);
}