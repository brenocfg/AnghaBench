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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtProtectVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtWriteVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  PAGE_EXECUTE_READWRITE ; 
 int /*<<< orphan*/  STATUS_MEMORY_NOT_ALLOCATED ; 

__attribute__((used)) static BOOL Write(PBYTE Address, PBYTE Data, SIZE_T Size)
{
    PVOID BaseAddress = Address;
    SIZE_T RegionSize = Size;
    ULONG OldProtection;
    NTSTATUS Status = NtProtectVirtualMemory(NtCurrentProcess(), &BaseAddress, &RegionSize, PAGE_EXECUTE_READWRITE, &OldProtection);
    if (NT_SUCCESS(Status))
    {
        SIZE_T Bytes;
        Status = NtWriteVirtualMemory(NtCurrentProcess(), Address, Data, Size, &Bytes);
        if (NT_SUCCESS(Status) && Bytes != Size)
            Status = STATUS_MEMORY_NOT_ALLOCATED;
        NtProtectVirtualMemory(NtCurrentProcess(), &BaseAddress, &RegionSize, OldProtection, &OldProtection);
    }
    return NT_SUCCESS(Status);
}