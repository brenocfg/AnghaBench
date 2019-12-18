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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  SyncRepUpdateSyncStandbysDefined () ; 
 int /*<<< orphan*/  UpdateFullPageWrites () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
UpdateSharedMemoryConfig(void)
{
	/* update global shmem state for sync rep */
	SyncRepUpdateSyncStandbysDefined();

	/*
	 * If full_page_writes has been changed by SIGHUP, we update it in shared
	 * memory and write an XLOG_FPW_CHANGE record.
	 */
	UpdateFullPageWrites();

	elog(DEBUG2, "checkpointer updated shared memory configuration values");
}