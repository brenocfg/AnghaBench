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
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CacheInitializeDrive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2DiskGeometry ; 
 int /*<<< orphan*/  Ext2DriveNumber ; 
 int /*<<< orphan*/  Ext2ReadGroupDescriptors () ; 
 int /*<<< orphan*/  Ext2ReadSuperBlock () ; 
 int /*<<< orphan*/  Ext2VolumeStartSector ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MachDiskGetDriveGeometry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Ext2OpenVolume(UCHAR DriveNumber, ULONGLONG VolumeStartSector, ULONGLONG PartitionSectorCount)
{

    TRACE("Ext2OpenVolume() DriveNumber = 0x%x VolumeStartSector = %d\n", DriveNumber, VolumeStartSector);

    // Store the drive number and start sector
    Ext2DriveNumber = DriveNumber;
    Ext2VolumeStartSector = VolumeStartSector;

    if (!MachDiskGetDriveGeometry(DriveNumber, &Ext2DiskGeometry))
    {
        return FALSE;
    }

    //
    // Initialize the disk cache for this drive
    //
    if (!CacheInitializeDrive(DriveNumber))
    {
        return FALSE;
    }

    // Read in the super block
    if (!Ext2ReadSuperBlock())
    {
        return FALSE;
    }

    // Read in the group descriptors
    if (!Ext2ReadGroupDescriptors())
    {
        return FALSE;
    }

    return TRUE;
}