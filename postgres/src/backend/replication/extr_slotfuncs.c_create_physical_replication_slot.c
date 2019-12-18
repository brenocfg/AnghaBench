#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_3__ {int /*<<< orphan*/  restart_lsn; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* MyReplicationSlot ; 
 int /*<<< orphan*/  RS_PERSISTENT ; 
 int /*<<< orphan*/  RS_TEMPORARY ; 
 int /*<<< orphan*/  ReplicationSlotCreate (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReplicationSlotMarkDirty () ; 
 int /*<<< orphan*/  ReplicationSlotReserveWal () ; 
 int /*<<< orphan*/  ReplicationSlotSave () ; 
 scalar_t__ XLogRecPtrIsInvalid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_physical_replication_slot(char *name, bool immediately_reserve,
								 bool temporary, XLogRecPtr restart_lsn)
{
	Assert(!MyReplicationSlot);

	/* acquire replication slot, this will check for conflicting names */
	ReplicationSlotCreate(name, false,
						  temporary ? RS_TEMPORARY : RS_PERSISTENT);

	if (immediately_reserve)
	{
		/* Reserve WAL as the user asked for it */
		if (XLogRecPtrIsInvalid(restart_lsn))
			ReplicationSlotReserveWal();
		else
			MyReplicationSlot->data.restart_lsn = restart_lsn;

		/* Write this slot to disk */
		ReplicationSlotMarkDirty();
		ReplicationSlotSave();
	}
}