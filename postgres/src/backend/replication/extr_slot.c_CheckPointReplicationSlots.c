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
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ data; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_2__ ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int MAXPGPATH ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReplicationSlotAllocationLock ; 
 TYPE_4__* ReplicationSlotCtl ; 
 int /*<<< orphan*/  SaveSlotToPath (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int max_replication_slots ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void
CheckPointReplicationSlots(void)
{
	int			i;

	elog(DEBUG1, "performing replication slot checkpoint");

	/*
	 * Prevent any slot from being created/dropped while we're active. As we
	 * explicitly do *not* want to block iterating over replication_slots or
	 * acquiring a slot we cannot take the control lock - but that's OK,
	 * because holding ReplicationSlotAllocationLock is strictly stronger, and
	 * enough to guarantee that nobody can change the in_use bits on us.
	 */
	LWLockAcquire(ReplicationSlotAllocationLock, LW_SHARED);

	for (i = 0; i < max_replication_slots; i++)
	{
		ReplicationSlot *s = &ReplicationSlotCtl->replication_slots[i];
		char		path[MAXPGPATH];

		if (!s->in_use)
			continue;

		/* save the slot to disk, locking is handled in SaveSlotToPath() */
		sprintf(path, "pg_replslot/%s", NameStr(s->data.name));
		SaveSlotToPath(s, path, LOG);
	}
	LWLockRelease(ReplicationSlotAllocationLock);
}