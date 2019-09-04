#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONGLONG ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int SectorSize; int /*<<< orphan*/  DriveNumber; scalar_t__ SectorOffset; scalar_t__ SectorNumber; } ;
typedef  TYPE_1__ DISKCONTEXT ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DiskReadBuffer ; 
 int DiskReadBufferSize ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_1__* FsGetDeviceSpecific (int) ; 
 int /*<<< orphan*/  MachDiskReadLogicalSectors (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static ARC_STATUS
DiskRead(ULONG FileId, VOID* Buffer, ULONG N, ULONG* Count)
{
    DISKCONTEXT* Context = FsGetDeviceSpecific(FileId);
    UCHAR* Ptr = (UCHAR*)Buffer;
    ULONG Length, TotalSectors, MaxSectors, ReadSectors;
    BOOLEAN ret;
    ULONGLONG SectorOffset;

    TotalSectors = (N + Context->SectorSize - 1) / Context->SectorSize;
    MaxSectors   = DiskReadBufferSize / Context->SectorSize;
    SectorOffset = Context->SectorNumber + Context->SectorOffset;

    ret = TRUE;

    while (TotalSectors)
    {
        ReadSectors = TotalSectors;
        if (ReadSectors > MaxSectors)
            ReadSectors = MaxSectors;

        ret = MachDiskReadLogicalSectors(Context->DriveNumber,
                                         SectorOffset,
                                         ReadSectors,
                                         DiskReadBuffer);
        if (!ret)
            break;

        Length = ReadSectors * Context->SectorSize;
        if (Length > N)
            Length = N;

        RtlCopyMemory(Ptr, DiskReadBuffer, Length);

        Ptr += Length;
        N -= Length;
        SectorOffset += ReadSectors;
        TotalSectors -= ReadSectors;
    }

    *Count = (ULONG)(Ptr - (UCHAR*)Buffer);

    return (!ret) ? EIO : ESUCCESS;
}