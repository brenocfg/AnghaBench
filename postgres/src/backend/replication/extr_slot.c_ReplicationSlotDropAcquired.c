#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MyReplicationSlot ; 
 int /*<<< orphan*/  ReplicationSlotDropPtr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ReplicationSlotDropAcquired(void)
{
	ReplicationSlot *slot = MyReplicationSlot;

	Assert(MyReplicationSlot != NULL);

	/* slot isn't acquired anymore */
	MyReplicationSlot = NULL;

	ReplicationSlotDropPtr(slot);
}