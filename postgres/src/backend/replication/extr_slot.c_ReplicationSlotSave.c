#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXPGPATH ; 
 TYPE_2__* MyReplicationSlot ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SaveSlotToPath (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void
ReplicationSlotSave(void)
{
	char		path[MAXPGPATH];

	Assert(MyReplicationSlot != NULL);

	sprintf(path, "pg_replslot/%s", NameStr(MyReplicationSlot->data.name));
	SaveSlotToPath(MyReplicationSlot, path, ERROR);
}