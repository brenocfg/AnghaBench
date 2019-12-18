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
 int /*<<< orphan*/  CreateSharedMemoryAndSemaphores () ; 

__attribute__((used)) static void
reset_shared(void)
{
	/*
	 * Create or re-create shared memory and semaphores.
	 *
	 * Note: in each "cycle of life" we will normally assign the same IPC keys
	 * (if using SysV shmem and/or semas).  This helps ensure that we will
	 * clean up dead IPC objects if the postmaster crashes and is restarted.
	 */
	CreateSharedMemoryAndSemaphores();
}