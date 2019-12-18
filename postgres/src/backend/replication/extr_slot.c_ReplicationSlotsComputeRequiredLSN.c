#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_6__ {TYPE_2__* replication_slots; } ;
struct TYPE_4__ {scalar_t__ restart_lsn; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; TYPE_1__ data; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_2__ ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  ReplicationSlotControlLock ; 
 TYPE_3__* ReplicationSlotCtl ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogSetReplicationSlotMinimumLSN (scalar_t__) ; 
 int max_replication_slots ; 

void
ReplicationSlotsComputeRequiredLSN(void)
{
	int			i;
	XLogRecPtr	min_required = InvalidXLogRecPtr;

	Assert(ReplicationSlotCtl != NULL);

	LWLockAcquire(ReplicationSlotControlLock, LW_SHARED);
	for (i = 0; i < max_replication_slots; i++)
	{
		ReplicationSlot *s = &ReplicationSlotCtl->replication_slots[i];
		XLogRecPtr	restart_lsn;

		if (!s->in_use)
			continue;

		SpinLockAcquire(&s->mutex);
		restart_lsn = s->data.restart_lsn;
		SpinLockRelease(&s->mutex);

		if (restart_lsn != InvalidXLogRecPtr &&
			(min_required == InvalidXLogRecPtr ||
			 restart_lsn < min_required))
			min_required = restart_lsn;
	}
	LWLockRelease(ReplicationSlotControlLock);

	XLogSetReplicationSlotMinimumLSN(min_required);
}