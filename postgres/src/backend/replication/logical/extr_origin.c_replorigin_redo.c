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
struct TYPE_9__ {int /*<<< orphan*/  force; int /*<<< orphan*/  remote_lsn; int /*<<< orphan*/  node_id; } ;
typedef  TYPE_1__ xl_replorigin_set ;
struct TYPE_10__ {int /*<<< orphan*/  node_id; } ;
typedef  TYPE_2__ xl_replorigin_drop ;
typedef  int uint8 ;
struct TYPE_11__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_3__ XLogReaderState ;
struct TYPE_12__ {void* local_lsn; void* remote_lsn; int /*<<< orphan*/  roident; } ;
typedef  TYPE_4__ ReplicationState ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidRepOriginId ; 
 void* InvalidXLogRecPtr ; 
 int /*<<< orphan*/  PANIC ; 
#define  XLOG_REPLORIGIN_DROP 129 
#define  XLOG_REPLORIGIN_SET 128 
 int XLR_INFO_MASK ; 
 scalar_t__ XLogRecGetData (TYPE_3__*) ; 
 int XLogRecGetInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int max_replication_slots ; 
 TYPE_4__* replication_states ; 
 int /*<<< orphan*/  replorigin_advance (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
replorigin_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	switch (info)
	{
		case XLOG_REPLORIGIN_SET:
			{
				xl_replorigin_set *xlrec =
				(xl_replorigin_set *) XLogRecGetData(record);

				replorigin_advance(xlrec->node_id,
								   xlrec->remote_lsn, record->EndRecPtr,
								   xlrec->force /* backward */ ,
								   false /* WAL log */ );
				break;
			}
		case XLOG_REPLORIGIN_DROP:
			{
				xl_replorigin_drop *xlrec;
				int			i;

				xlrec = (xl_replorigin_drop *) XLogRecGetData(record);

				for (i = 0; i < max_replication_slots; i++)
				{
					ReplicationState *state = &replication_states[i];

					/* found our slot */
					if (state->roident == xlrec->node_id)
					{
						/* reset entry */
						state->roident = InvalidRepOriginId;
						state->remote_lsn = InvalidXLogRecPtr;
						state->local_lsn = InvalidXLogRecPtr;
						break;
					}
				}
				break;
			}
		default:
			elog(PANIC, "replorigin_redo: unknown op code %u", info);
	}
}