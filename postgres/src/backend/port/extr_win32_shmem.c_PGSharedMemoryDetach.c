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
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/ * ShmemProtectiveRegion ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UsedShmemSegAddr ; 
 scalar_t__ UsedShmemSegID ; 
 scalar_t__ VirtualFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void
PGSharedMemoryDetach(void)
{
	/*
	 * Releasing the protective region liberates an unimportant quantity of
	 * address space, but be tidy.
	 */
	if (ShmemProtectiveRegion != NULL)
	{
		if (VirtualFree(ShmemProtectiveRegion, 0, MEM_RELEASE) == 0)
			elog(LOG, "failed to release reserved memory region (addr=%p): error code %lu",
				 ShmemProtectiveRegion, GetLastError());

		ShmemProtectiveRegion = NULL;
	}

	/* Unmap the view, if it's mapped */
	if (UsedShmemSegAddr != NULL)
	{
		if (!UnmapViewOfFile(UsedShmemSegAddr))
			elog(LOG, "could not unmap view of shared memory: error code %lu",
				 GetLastError());

		UsedShmemSegAddr = NULL;
	}

	/* And close the shmem handle, if we have one */
	if (UsedShmemSegID != INVALID_HANDLE_VALUE)
	{
		if (!CloseHandle(UsedShmemSegID))
			elog(LOG, "could not close handle to shared memory: error code %lu",
				 GetLastError());

		UsedShmemSegID = INVALID_HANDLE_VALUE;
	}
}