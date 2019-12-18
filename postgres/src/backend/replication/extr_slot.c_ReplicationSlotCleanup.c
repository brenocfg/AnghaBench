#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* replication_slots; } ;
struct TYPE_5__ {scalar_t__ persistency; } ;
struct TYPE_6__ {scalar_t__ active_pid; int /*<<< orphan*/  mutex; int /*<<< orphan*/  active_cv; TYPE_1__ data; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_2__ ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ConditionVariableBroadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/ * MyReplicationSlot ; 
 scalar_t__ RS_TEMPORARY ; 
 int /*<<< orphan*/  ReplicationSlotControlLock ; 
 TYPE_4__* ReplicationSlotCtl ; 
 int /*<<< orphan*/  ReplicationSlotDropPtr (TYPE_2__*) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int max_replication_slots ; 

void
ReplicationSlotCleanup(void)
{
	int			i;

	Assert(MyReplicationSlot == NULL);

restart:
	LWLockAcquire(ReplicationSlotControlLock, LW_SHARED);
	for (i = 0; i < max_replication_slots; i++)
	{
		ReplicationSlot *s = &ReplicationSlotCtl->replication_slots[i];

		if (!s->in_use)
			continue;

		SpinLockAcquire(&s->mutex);
		if (s->active_pid == MyProcPid)
		{
			Assert(s->data.persistency == RS_TEMPORARY);
			SpinLockRelease(&s->mutex);
			LWLockRelease(ReplicationSlotControlLock);	/* avoid deadlock */

			ReplicationSlotDropPtr(s);

			ConditionVariableBroadcast(&s->active_cv);
			goto restart;
		}
		else
			SpinLockRelease(&s->mutex);
	}

	LWLockRelease(ReplicationSlotControlLock);
}