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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ESUCCESS ; 
 scalar_t__ RamDiskBase ; 
 scalar_t__ RamDiskImageLength ; 
 scalar_t__ RamDiskImageOffset ; 
 scalar_t__ RamDiskOffset ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static ARC_STATUS RamDiskRead(ULONG FileId, VOID* Buffer, ULONG N, ULONG* Count)
{
    PVOID StartAddress;

    /* Don't allow reads past our image */
    if (RamDiskOffset >= RamDiskImageLength || RamDiskOffset + N > RamDiskImageLength)
    {
        *Count = 0;
        return EIO;
    }
    // N = min(N, RamdiskImageLength - RamDiskOffset);

    /* Get actual pointer */
    StartAddress = (PVOID)((ULONG_PTR)RamDiskBase + RamDiskImageOffset + (ULONG_PTR)RamDiskOffset);

    /* Do the read */
    RtlCopyMemory(Buffer, StartAddress, N);
    RamDiskOffset += N;
    *Count = N;

    return ESUCCESS;
}