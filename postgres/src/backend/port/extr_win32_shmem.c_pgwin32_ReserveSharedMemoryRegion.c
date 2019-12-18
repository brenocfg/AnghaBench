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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MEM_RESERVE ; 
 int /*<<< orphan*/  PAGE_NOACCESS ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 scalar_t__ PROTECTIVE_REGION_SIZE ; 
 void* ShmemProtectiveRegion ; 
 void* UsedShmemSegAddr ; 
 scalar_t__ UsedShmemSegSize ; 
 void* VirtualAllocEx (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*,void*,...) ; 

int
pgwin32_ReserveSharedMemoryRegion(HANDLE hChild)
{
	void	   *address;

	Assert(ShmemProtectiveRegion != NULL);
	Assert(UsedShmemSegAddr != NULL);
	Assert(UsedShmemSegSize != 0);

	/* ShmemProtectiveRegion */
	address = VirtualAllocEx(hChild, ShmemProtectiveRegion,
							 PROTECTIVE_REGION_SIZE,
							 MEM_RESERVE, PAGE_NOACCESS);
	if (address == NULL)
	{
		/* Don't use FATAL since we're running in the postmaster */
		elog(LOG, "could not reserve shared memory region (addr=%p) for child %p: error code %lu",
			 ShmemProtectiveRegion, hChild, GetLastError());
		return false;
	}
	if (address != ShmemProtectiveRegion)
	{
		/*
		 * Should never happen - in theory if allocation granularity causes
		 * strange effects it could, so check just in case.
		 *
		 * Don't use FATAL since we're running in the postmaster.
		 */
		elog(LOG, "reserved shared memory region got incorrect address %p, expected %p",
			 address, ShmemProtectiveRegion);
		return false;
	}

	/* UsedShmemSegAddr */
	address = VirtualAllocEx(hChild, UsedShmemSegAddr, UsedShmemSegSize,
							 MEM_RESERVE, PAGE_READWRITE);
	if (address == NULL)
	{
		elog(LOG, "could not reserve shared memory region (addr=%p) for child %p: error code %lu",
			 UsedShmemSegAddr, hChild, GetLastError());
		return false;
	}
	if (address != UsedShmemSegAddr)
	{
		elog(LOG, "reserved shared memory region got incorrect address %p, expected %p",
			 address, UsedShmemSegAddr);
		return false;
	}

	return true;
}