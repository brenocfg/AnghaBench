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
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ gRamDiskBase ; 
 scalar_t__ gRamDiskOffset ; 
 scalar_t__ gRamDiskSize ; 

__attribute__((used)) static ARC_STATUS RamDiskRead(ULONG FileId, VOID* Buffer, ULONG N, ULONG* Count)
{
    PVOID StartAddress;

    //
    // Get actual pointer
    //
    StartAddress = (PVOID)((ULONG_PTR)gRamDiskBase + gRamDiskOffset);

    //
    // Don't allow reads past our image
    //
    if (gRamDiskOffset + N > gRamDiskSize)
    {
        *Count = 0;
        return EIO;
    }

    //
    // Do the read
    //
    RtlCopyMemory(Buffer, StartAddress, N);
    *Count = N;

    return ESUCCESS;
}