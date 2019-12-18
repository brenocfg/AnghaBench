#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * relids; } ;
struct TYPE_9__ {TYPE_5__* message; TYPE_5__* prefix; } ;
struct TYPE_8__ {int /*<<< orphan*/ * oldtuple; int /*<<< orphan*/ * newtuple; } ;
struct TYPE_11__ {TYPE_3__ truncate; int /*<<< orphan*/ * snapshot; TYPE_2__ msg; TYPE_1__ tp; } ;
struct TYPE_12__ {int action; TYPE_4__ data; } ;
typedef  TYPE_5__ ReorderBufferChange ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
#define  REORDER_BUFFER_CHANGE_DELETE 137 
#define  REORDER_BUFFER_CHANGE_INSERT 136 
#define  REORDER_BUFFER_CHANGE_INTERNAL_COMMAND_ID 135 
#define  REORDER_BUFFER_CHANGE_INTERNAL_SNAPSHOT 134 
#define  REORDER_BUFFER_CHANGE_INTERNAL_SPEC_CONFIRM 133 
#define  REORDER_BUFFER_CHANGE_INTERNAL_SPEC_INSERT 132 
#define  REORDER_BUFFER_CHANGE_INTERNAL_TUPLECID 131 
#define  REORDER_BUFFER_CHANGE_MESSAGE 130 
#define  REORDER_BUFFER_CHANGE_TRUNCATE 129 
#define  REORDER_BUFFER_CHANGE_UPDATE 128 
 int /*<<< orphan*/  ReorderBufferFreeSnap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReorderBufferReturnRelids (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReorderBufferReturnTupleBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_5__*) ; 

void
ReorderBufferReturnChange(ReorderBuffer *rb, ReorderBufferChange *change)
{
	/* free contained data */
	switch (change->action)
	{
		case REORDER_BUFFER_CHANGE_INSERT:
		case REORDER_BUFFER_CHANGE_UPDATE:
		case REORDER_BUFFER_CHANGE_DELETE:
		case REORDER_BUFFER_CHANGE_INTERNAL_SPEC_INSERT:
			if (change->data.tp.newtuple)
			{
				ReorderBufferReturnTupleBuf(rb, change->data.tp.newtuple);
				change->data.tp.newtuple = NULL;
			}

			if (change->data.tp.oldtuple)
			{
				ReorderBufferReturnTupleBuf(rb, change->data.tp.oldtuple);
				change->data.tp.oldtuple = NULL;
			}
			break;
		case REORDER_BUFFER_CHANGE_MESSAGE:
			if (change->data.msg.prefix != NULL)
				pfree(change->data.msg.prefix);
			change->data.msg.prefix = NULL;
			if (change->data.msg.message != NULL)
				pfree(change->data.msg.message);
			change->data.msg.message = NULL;
			break;
		case REORDER_BUFFER_CHANGE_INTERNAL_SNAPSHOT:
			if (change->data.snapshot)
			{
				ReorderBufferFreeSnap(rb, change->data.snapshot);
				change->data.snapshot = NULL;
			}
			break;
			/* no data in addition to the struct itself */
		case REORDER_BUFFER_CHANGE_TRUNCATE:
			if (change->data.truncate.relids != NULL)
			{
				ReorderBufferReturnRelids(rb, change->data.truncate.relids);
				change->data.truncate.relids = NULL;
			}
			break;
		case REORDER_BUFFER_CHANGE_INTERNAL_SPEC_CONFIRM:
		case REORDER_BUFFER_CHANGE_INTERNAL_COMMAND_ID:
		case REORDER_BUFFER_CHANGE_INTERNAL_TUPLECID:
			break;
	}

	pfree(change);
}