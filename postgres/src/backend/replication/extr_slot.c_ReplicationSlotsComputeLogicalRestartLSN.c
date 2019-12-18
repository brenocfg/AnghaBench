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
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_7__ {TYPE_2__* replication_slots; } ;
struct TYPE_5__ {scalar_t__ restart_lsn; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_1__ data; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_2__ ReplicationSlot ;

/* Variables and functions */
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  ReplicationSlotControlLock ; 
 TYPE_4__* ReplicationSlotCtl ; 
 int /*<<< orphan*/  SlotIsLogical (TYPE_2__*) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int max_replication_slots ; 

XLogRecPtr
ReplicationSlotsComputeLogicalRestartLSN(void)
{
	XLogRecPtr	result = InvalidXLogRecPtr;
	int			i;

	if (max_replication_slots <= 0)
		return InvalidXLogRecPtr;

	LWLockAcquire(ReplicationSlotControlLock, LW_SHARED);

	for (i = 0; i < max_replication_slots; i++)
	{
		ReplicationSlot *s;
		XLogRecPtr	restart_lsn;

		s = &ReplicationSlotCtl->replication_slots[i];

		/* cannot change while ReplicationSlotCtlLock is held */
		if (!s->in_use)
			continue;

		/* we're only interested in logical slots */
		if (!SlotIsLogical(s))
			continue;

		/* read once, it's ok if it increases while we're checking */
		SpinLockAcquire(&s->mutex);
		restart_lsn = s->data.restart_lsn;
		SpinLockRelease(&s->mutex);

		if (result == InvalidXLogRecPtr ||
			restart_lsn < result)
			result = restart_lsn;
	}

	LWLockRelease(ReplicationSlotControlLock);

	return result;
}