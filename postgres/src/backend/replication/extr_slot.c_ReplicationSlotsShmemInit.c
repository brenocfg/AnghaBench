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
struct TYPE_6__ {int /*<<< orphan*/  active_cv; int /*<<< orphan*/  io_in_progress_lock; int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {TYPE_2__* replication_slots; } ;
typedef  TYPE_1__ ReplicationSlotCtlData ;
typedef  TYPE_2__ ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  ConditionVariableInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRegisterTranche (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWTRANCHE_REPLICATION_SLOT_IO_IN_PROGRESS ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ReplicationSlotCtl ; 
 int /*<<< orphan*/  ReplicationSlotsShmemSize () ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 int max_replication_slots ; 

void
ReplicationSlotsShmemInit(void)
{
	bool		found;

	if (max_replication_slots == 0)
		return;

	ReplicationSlotCtl = (ReplicationSlotCtlData *)
		ShmemInitStruct("ReplicationSlot Ctl", ReplicationSlotsShmemSize(),
						&found);

	LWLockRegisterTranche(LWTRANCHE_REPLICATION_SLOT_IO_IN_PROGRESS,
						  "replication_slot_io");

	if (!found)
	{
		int			i;

		/* First time through, so initialize */
		MemSet(ReplicationSlotCtl, 0, ReplicationSlotsShmemSize());

		for (i = 0; i < max_replication_slots; i++)
		{
			ReplicationSlot *slot = &ReplicationSlotCtl->replication_slots[i];

			/* everything else is zeroed by the memset above */
			SpinLockInit(&slot->mutex);
			LWLockInitialize(&slot->io_in_progress_lock, LWTRANCHE_REPLICATION_SLOT_IO_IN_PROGRESS);
			ConditionVariableInit(&slot->active_cv);
		}
	}
}