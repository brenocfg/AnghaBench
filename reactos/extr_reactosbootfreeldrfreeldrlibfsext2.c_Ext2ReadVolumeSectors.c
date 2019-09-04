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
typedef  scalar_t__ ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CacheReadDiskSectors (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Ext2VolumeStartSector ; 

BOOLEAN Ext2ReadVolumeSectors(UCHAR DriveNumber, ULONGLONG SectorNumber, ULONG SectorCount, PVOID Buffer)
{
    //GEOMETRY    DiskGeometry;
    //BOOLEAN        ReturnValue;
    //if (!DiskGetDriveGeometry(DriveNumber, &DiskGeometry))
    //{
    //    return FALSE;
    //}
    //ReturnValue = MachDiskReadLogicalSectors(DriveNumber, SectorNumber + Ext2VolumeStartSector, SectorCount, DiskReadBuffer);
    //RtlCopyMemory(Buffer, DiskReadBuffer, SectorCount * DiskGeometry.BytesPerSector);
    //return ReturnValue;

    return CacheReadDiskSectors(DriveNumber, SectorNumber + Ext2VolumeStartSector, SectorCount, Buffer);
}