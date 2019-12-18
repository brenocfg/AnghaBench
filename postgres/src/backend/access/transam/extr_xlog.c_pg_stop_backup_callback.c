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
struct TYPE_3__ {scalar_t__ exclusiveBackupState; } ;
struct TYPE_4__ {TYPE_1__ Insert; } ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 scalar_t__ EXCLUSIVE_BACKUP_IN_PROGRESS ; 
 scalar_t__ EXCLUSIVE_BACKUP_STOPPING ; 
 int /*<<< orphan*/  WALInsertLockAcquireExclusive () ; 
 int /*<<< orphan*/  WALInsertLockRelease () ; 
 TYPE_2__* XLogCtl ; 

__attribute__((used)) static void
pg_stop_backup_callback(int code, Datum arg)
{
	bool		exclusive = DatumGetBool(arg);

	/* Update backup status on failure */
	WALInsertLockAcquireExclusive();
	if (exclusive)
	{
		Assert(XLogCtl->Insert.exclusiveBackupState == EXCLUSIVE_BACKUP_STOPPING);
		XLogCtl->Insert.exclusiveBackupState = EXCLUSIVE_BACKUP_IN_PROGRESS;
	}
	WALInsertLockRelease();
}