#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* ULONGLONG ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int SectorSize; scalar_t__ SectorNumber; void* SectorCount; void* SectorOffset; int /*<<< orphan*/  DriveNumber; } ;
struct TYPE_6__ {void* PartitionSectorCount; void* SectorCountBeforePartition; } ;
typedef  TYPE_1__ PARTITION_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  OPENMODE ;
typedef  TYPE_2__ DISKCONTEXT ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DiskGetPartitionEntry (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  DissectArcPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_2__* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsSetDeviceSpecific (int,TYPE_2__*) ; 
 int /*<<< orphan*/  TAG_HW_DISK_CONTEXT ; 

__attribute__((used)) static ARC_STATUS
DiskOpen(CHAR* Path, OPENMODE OpenMode, ULONG* FileId)
{
    DISKCONTEXT* Context;
    UCHAR DriveNumber;
    ULONG DrivePartition, SectorSize;
    ULONGLONG SectorOffset = 0;
    ULONGLONG SectorCount = 0;
    PARTITION_TABLE_ENTRY PartitionTableEntry;
    CHAR FileName[1];

    if (!DissectArcPath(Path, FileName, &DriveNumber, &DrivePartition))
        return EINVAL;

    if (DrivePartition == 0xff)
    {
        /* This is a CD-ROM device */
        SectorSize = 2048;
    }
    else
    {
        /*
         * This is either a floppy disk device (DrivePartition == 0) or
         * a hard disk device (DrivePartition != 0 && DrivePartition != 0xFF)
         * but it doesn't matter which one because they both have 512 bytes
         * per sector.
         */
        SectorSize = 512;
    }

    if (DrivePartition != 0xff && DrivePartition != 0)
    {
        if (!DiskGetPartitionEntry(DriveNumber, DrivePartition, &PartitionTableEntry))
            return EINVAL;

        SectorOffset = PartitionTableEntry.SectorCountBeforePartition;
        SectorCount = PartitionTableEntry.PartitionSectorCount;
    }
#if 0 // FIXME: Investigate
    else
    {
        SectorCount = 0; /* FIXME */
    }
#endif

    Context = FrLdrTempAlloc(sizeof(DISKCONTEXT), TAG_HW_DISK_CONTEXT);
    if (!Context)
        return ENOMEM;

    Context->DriveNumber = DriveNumber;
    Context->SectorSize = SectorSize;
    Context->SectorOffset = SectorOffset;
    Context->SectorCount = SectorCount;
    Context->SectorNumber = 0;
    FsSetDeviceSpecific(*FileId, Context);

    return ESUCCESS;
}