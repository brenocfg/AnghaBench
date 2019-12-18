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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  SYSTEM_INFORMATION_CLASS ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ NTSTATUS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ NtQuerySystemInformation (int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 

NTSTATUS kull_m_process_NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS informationClass, PVOID buffer, ULONG informationLength)
{
	NTSTATUS status = STATUS_INFO_LENGTH_MISMATCH;
	DWORD sizeOfBuffer, returnedLen;

	if(*(PVOID *) buffer)
	{
		status = NtQuerySystemInformation(informationClass, *(PVOID *) buffer, informationLength, &returnedLen);
	}
	else
	{
		for(sizeOfBuffer = 0x1000; (status == STATUS_INFO_LENGTH_MISMATCH) && (*(PVOID *) buffer = LocalAlloc(LPTR, sizeOfBuffer)) ; sizeOfBuffer <<= 1)
		{
			status = NtQuerySystemInformation(informationClass, *(PVOID *) buffer, sizeOfBuffer, &returnedLen);
			if(!NT_SUCCESS(status))
				LocalFree(*(PVOID *) buffer);
		}
	}
	return status;
}