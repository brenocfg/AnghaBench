#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  slotname; } ;
typedef  TYPE_1__ DropReplicationSlotCmd ;

/* Variables and functions */
 int /*<<< orphan*/  DestRemote ; 
 int /*<<< orphan*/  EndCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReplicationSlotDrop (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
DropReplicationSlot(DropReplicationSlotCmd *cmd)
{
	ReplicationSlotDrop(cmd->slotname, !cmd->wait);
	EndCommand("DROP_REPLICATION_SLOT", DestRemote);
}