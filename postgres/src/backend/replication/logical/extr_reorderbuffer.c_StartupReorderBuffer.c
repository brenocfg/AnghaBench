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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReorderBufferCleanupSerializedTXNs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReplicationSlotValidateName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void
StartupReorderBuffer(void)
{
	DIR		   *logical_dir;
	struct dirent *logical_de;

	logical_dir = AllocateDir("pg_replslot");
	while ((logical_de = ReadDir(logical_dir, "pg_replslot")) != NULL)
	{
		if (strcmp(logical_de->d_name, ".") == 0 ||
			strcmp(logical_de->d_name, "..") == 0)
			continue;

		/* if it cannot be a slot, skip the directory */
		if (!ReplicationSlotValidateName(logical_de->d_name, DEBUG2))
			continue;

		/*
		 * ok, has to be a surviving logical slot, iterate and delete
		 * everything starting with xid-*
		 */
		ReorderBufferCleanupSerializedTXNs(logical_de->d_name);
	}
	FreeDir(logical_dir);
}