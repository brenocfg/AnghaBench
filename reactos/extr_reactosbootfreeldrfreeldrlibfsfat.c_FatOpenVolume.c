#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_14__ {int BytesPerSector; int SectorsPerCluster; int ReservedSectors; int NumberOfFats; int RootDirEntries; int TotalSectors; int MediaDescriptor; int SectorsPerFat; int SectorsPerTrack; int NumberOfHeads; int HiddenSectors; int TotalSectorsBig; int SectorsPerFatBig; int ExtendedFlags; int FileSystemVersion; int RootDirStartCluster; int FsInfo; int BackupBootSector; int Reserved; int DriveNumber; int Reserved1; int BootSignature; int VolumeSerialNumber; int BootSectorMagic; int /*<<< orphan*/ * FileSystemType; int /*<<< orphan*/ * VolumeLabel; int /*<<< orphan*/ * OemName; int /*<<< orphan*/ * JumpBoot; } ;
struct TYPE_13__ {int VolumeSerialNumber; int SectorsPerCluster; int NumberOfFats; int Unknown; int /*<<< orphan*/ * FileSystemType; } ;
struct TYPE_12__ {int BytesPerSector; int SectorsPerCluster; int ReservedSectors; int NumberOfFats; int RootDirEntries; int TotalSectors; int MediaDescriptor; int SectorsPerFat; int SectorsPerTrack; int NumberOfHeads; int HiddenSectors; int TotalSectorsBig; int DriveNumber; int Reserved1; int BootSignature; int VolumeSerialNumber; int BootSectorMagic; int /*<<< orphan*/ * FileSystemType; int /*<<< orphan*/ * VolumeLabel; int /*<<< orphan*/ * OemName; int /*<<< orphan*/ * JumpBoot; } ;
struct TYPE_11__ {int DeviceId; int BytesPerSector; int SectorsPerCluster; int FatSectorStart; int ActiveFatSectorStart; int NumberOfFats; int SectorsPerFat; int RootDirSectorStart; int RootDirSectors; int DataSectorStart; int RootDirStartCluster; int /*<<< orphan*/  FatType; } ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;
typedef  TYPE_2__* PFAT_BOOTSECTOR ;
typedef  TYPE_3__* PFATX_BOOTSECTOR ;
typedef  TYPE_4__* PFAT32_BOOTSECTOR ;
typedef  int /*<<< orphan*/  FAT_BOOTSECTOR ;
typedef  int /*<<< orphan*/  FATX_BOOTSECTOR ;
typedef  int /*<<< orphan*/  FAT32_BOOTSECTOR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FAT32 ; 
 int /*<<< orphan*/  FATX16 ; 
 int /*<<< orphan*/  FatDetermineFatType (TYPE_2__*,int) ; 
 int /*<<< orphan*/  FatSwapFat32BootSector (TYPE_4__*) ; 
 int /*<<< orphan*/  FatSwapFatBootSector (TYPE_2__*) ; 
 int /*<<< orphan*/  FatSwapFatXBootSector (TYPE_3__*) ; 
 int /*<<< orphan*/  FileSystemError (char*) ; 
 scalar_t__ ISFATX (int /*<<< orphan*/ ) ; 
 int SWAPD (int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

BOOLEAN FatOpenVolume(PFAT_VOLUME_INFO Volume, PFAT_BOOTSECTOR BootSector, ULONGLONG PartitionSectorCount)
{
    char ErrMsg[80];
    ULONG FatSize;
    PFAT_BOOTSECTOR    FatVolumeBootSector;
    PFAT32_BOOTSECTOR Fat32VolumeBootSector;
    PFATX_BOOTSECTOR FatXVolumeBootSector;

    TRACE("FatOpenVolume() DeviceId = %d\n", Volume->DeviceId);

    //
    // Allocate the memory to hold the boot sector
    //
    FatVolumeBootSector = (PFAT_BOOTSECTOR)BootSector;
    Fat32VolumeBootSector = (PFAT32_BOOTSECTOR)BootSector;
    FatXVolumeBootSector = (PFATX_BOOTSECTOR)BootSector;

    // Get the FAT type
    Volume->FatType = FatDetermineFatType(FatVolumeBootSector, PartitionSectorCount);

    // Dump boot sector (and swap it for big endian systems)
    TRACE("Dumping boot sector:\n");
    if (ISFATX(Volume->FatType))
    {
        FatSwapFatXBootSector(FatXVolumeBootSector);
        TRACE("sizeof(FATX_BOOTSECTOR) = 0x%x.\n", sizeof(FATX_BOOTSECTOR));

        TRACE("FileSystemType: %c%c%c%c.\n", FatXVolumeBootSector->FileSystemType[0], FatXVolumeBootSector->FileSystemType[1], FatXVolumeBootSector->FileSystemType[2], FatXVolumeBootSector->FileSystemType[3]);
        TRACE("VolumeSerialNumber: 0x%x\n", FatXVolumeBootSector->VolumeSerialNumber);
        TRACE("SectorsPerCluster: %d\n", FatXVolumeBootSector->SectorsPerCluster);
        TRACE("NumberOfFats: %d\n", FatXVolumeBootSector->NumberOfFats);
        TRACE("Unknown: 0x%x\n", FatXVolumeBootSector->Unknown);

        TRACE("FatType %s\n", Volume->FatType == FATX16 ? "FATX16" : "FATX32");

    }
    else if (Volume->FatType == FAT32)
    {
        FatSwapFat32BootSector(Fat32VolumeBootSector);
        TRACE("sizeof(FAT32_BOOTSECTOR) = 0x%x.\n", sizeof(FAT32_BOOTSECTOR));

        TRACE("JumpBoot: 0x%x 0x%x 0x%x\n", Fat32VolumeBootSector->JumpBoot[0], Fat32VolumeBootSector->JumpBoot[1], Fat32VolumeBootSector->JumpBoot[2]);
        TRACE("OemName: %c%c%c%c%c%c%c%c\n", Fat32VolumeBootSector->OemName[0], Fat32VolumeBootSector->OemName[1], Fat32VolumeBootSector->OemName[2], Fat32VolumeBootSector->OemName[3], Fat32VolumeBootSector->OemName[4], Fat32VolumeBootSector->OemName[5], Fat32VolumeBootSector->OemName[6], Fat32VolumeBootSector->OemName[7]);
        TRACE("BytesPerSector: %d\n", Fat32VolumeBootSector->BytesPerSector);
        TRACE("SectorsPerCluster: %d\n", Fat32VolumeBootSector->SectorsPerCluster);
        TRACE("ReservedSectors: %d\n", Fat32VolumeBootSector->ReservedSectors);
        TRACE("NumberOfFats: %d\n", Fat32VolumeBootSector->NumberOfFats);
        TRACE("RootDirEntries: %d\n", Fat32VolumeBootSector->RootDirEntries);
        TRACE("TotalSectors: %d\n", Fat32VolumeBootSector->TotalSectors);
        TRACE("MediaDescriptor: 0x%x\n", Fat32VolumeBootSector->MediaDescriptor);
        TRACE("SectorsPerFat: %d\n", Fat32VolumeBootSector->SectorsPerFat);
        TRACE("SectorsPerTrack: %d\n", Fat32VolumeBootSector->SectorsPerTrack);
        TRACE("NumberOfHeads: %d\n", Fat32VolumeBootSector->NumberOfHeads);
        TRACE("HiddenSectors: %d\n", Fat32VolumeBootSector->HiddenSectors);
        TRACE("TotalSectorsBig: %d\n", Fat32VolumeBootSector->TotalSectorsBig);
        TRACE("SectorsPerFatBig: %d\n", Fat32VolumeBootSector->SectorsPerFatBig);
        TRACE("ExtendedFlags: 0x%x\n", Fat32VolumeBootSector->ExtendedFlags);
        TRACE("FileSystemVersion: 0x%x\n", Fat32VolumeBootSector->FileSystemVersion);
        TRACE("RootDirStartCluster: %d\n", Fat32VolumeBootSector->RootDirStartCluster);
        TRACE("FsInfo: %d\n", Fat32VolumeBootSector->FsInfo);
        TRACE("BackupBootSector: %d\n", Fat32VolumeBootSector->BackupBootSector);
        TRACE("Reserved: 0x%x\n", Fat32VolumeBootSector->Reserved);
        TRACE("DriveNumber: 0x%x\n", Fat32VolumeBootSector->DriveNumber);
        TRACE("Reserved1: 0x%x\n", Fat32VolumeBootSector->Reserved1);
        TRACE("BootSignature: 0x%x\n", Fat32VolumeBootSector->BootSignature);
        TRACE("VolumeSerialNumber: 0x%x\n", Fat32VolumeBootSector->VolumeSerialNumber);
        TRACE("VolumeLabel: %c%c%c%c%c%c%c%c%c%c%c\n", Fat32VolumeBootSector->VolumeLabel[0], Fat32VolumeBootSector->VolumeLabel[1], Fat32VolumeBootSector->VolumeLabel[2], Fat32VolumeBootSector->VolumeLabel[3], Fat32VolumeBootSector->VolumeLabel[4], Fat32VolumeBootSector->VolumeLabel[5], Fat32VolumeBootSector->VolumeLabel[6], Fat32VolumeBootSector->VolumeLabel[7], Fat32VolumeBootSector->VolumeLabel[8], Fat32VolumeBootSector->VolumeLabel[9], Fat32VolumeBootSector->VolumeLabel[10]);
        TRACE("FileSystemType: %c%c%c%c%c%c%c%c\n", Fat32VolumeBootSector->FileSystemType[0], Fat32VolumeBootSector->FileSystemType[1], Fat32VolumeBootSector->FileSystemType[2], Fat32VolumeBootSector->FileSystemType[3], Fat32VolumeBootSector->FileSystemType[4], Fat32VolumeBootSector->FileSystemType[5], Fat32VolumeBootSector->FileSystemType[6], Fat32VolumeBootSector->FileSystemType[7]);
        TRACE("BootSectorMagic: 0x%x\n", Fat32VolumeBootSector->BootSectorMagic);
    }
    else
    {
        FatSwapFatBootSector(FatVolumeBootSector);
        TRACE("sizeof(FAT_BOOTSECTOR) = 0x%x.\n", sizeof(FAT_BOOTSECTOR));

        TRACE("JumpBoot: 0x%x 0x%x 0x%x\n", FatVolumeBootSector->JumpBoot[0], FatVolumeBootSector->JumpBoot[1], FatVolumeBootSector->JumpBoot[2]);
        TRACE("OemName: %c%c%c%c%c%c%c%c\n", FatVolumeBootSector->OemName[0], FatVolumeBootSector->OemName[1], FatVolumeBootSector->OemName[2], FatVolumeBootSector->OemName[3], FatVolumeBootSector->OemName[4], FatVolumeBootSector->OemName[5], FatVolumeBootSector->OemName[6], FatVolumeBootSector->OemName[7]);
        TRACE("BytesPerSector: %d\n", FatVolumeBootSector->BytesPerSector);
        TRACE("SectorsPerCluster: %d\n", FatVolumeBootSector->SectorsPerCluster);
        TRACE("ReservedSectors: %d\n", FatVolumeBootSector->ReservedSectors);
        TRACE("NumberOfFats: %d\n", FatVolumeBootSector->NumberOfFats);
        TRACE("RootDirEntries: %d\n", FatVolumeBootSector->RootDirEntries);
        TRACE("TotalSectors: %d\n", FatVolumeBootSector->TotalSectors);
        TRACE("MediaDescriptor: 0x%x\n", FatVolumeBootSector->MediaDescriptor);
        TRACE("SectorsPerFat: %d\n", FatVolumeBootSector->SectorsPerFat);
        TRACE("SectorsPerTrack: %d\n", FatVolumeBootSector->SectorsPerTrack);
        TRACE("NumberOfHeads: %d\n", FatVolumeBootSector->NumberOfHeads);
        TRACE("HiddenSectors: %d\n", FatVolumeBootSector->HiddenSectors);
        TRACE("TotalSectorsBig: %d\n", FatVolumeBootSector->TotalSectorsBig);
        TRACE("DriveNumber: 0x%x\n", FatVolumeBootSector->DriveNumber);
        TRACE("Reserved1: 0x%x\n", FatVolumeBootSector->Reserved1);
        TRACE("BootSignature: 0x%x\n", FatVolumeBootSector->BootSignature);
        TRACE("VolumeSerialNumber: 0x%x\n", FatVolumeBootSector->VolumeSerialNumber);
        TRACE("VolumeLabel: %c%c%c%c%c%c%c%c%c%c%c\n", FatVolumeBootSector->VolumeLabel[0], FatVolumeBootSector->VolumeLabel[1], FatVolumeBootSector->VolumeLabel[2], FatVolumeBootSector->VolumeLabel[3], FatVolumeBootSector->VolumeLabel[4], FatVolumeBootSector->VolumeLabel[5], FatVolumeBootSector->VolumeLabel[6], FatVolumeBootSector->VolumeLabel[7], FatVolumeBootSector->VolumeLabel[8], FatVolumeBootSector->VolumeLabel[9], FatVolumeBootSector->VolumeLabel[10]);
        TRACE("FileSystemType: %c%c%c%c%c%c%c%c\n", FatVolumeBootSector->FileSystemType[0], FatVolumeBootSector->FileSystemType[1], FatVolumeBootSector->FileSystemType[2], FatVolumeBootSector->FileSystemType[3], FatVolumeBootSector->FileSystemType[4], FatVolumeBootSector->FileSystemType[5], FatVolumeBootSector->FileSystemType[6], FatVolumeBootSector->FileSystemType[7]);
        TRACE("BootSectorMagic: 0x%x\n", FatVolumeBootSector->BootSectorMagic);
    }

    //
    // Check the boot sector magic
    //
    if (! ISFATX(Volume->FatType) && FatVolumeBootSector->BootSectorMagic != 0xaa55)
    {
        sprintf(ErrMsg, "Invalid boot sector magic (expected 0xaa55 found 0x%x)",
                FatVolumeBootSector->BootSectorMagic);
        FileSystemError(ErrMsg);
        return FALSE;
    }

    //
    // Check the FAT cluster size
    // We do not support clusters bigger than 64k
    //
    if ((ISFATX(Volume->FatType) && 64 * 1024 < FatXVolumeBootSector->SectorsPerCluster * 512) ||
       (! ISFATX(Volume->FatType) && 64 * 1024 < FatVolumeBootSector->SectorsPerCluster * FatVolumeBootSector->BytesPerSector))
    {
        FileSystemError("This file system has cluster sizes bigger than 64k.\nFreeLoader does not support this.");
        return FALSE;
    }

    //
    // Get the sectors per FAT,
    // root directory starting sector,
    // and data sector start
    //
    if (ISFATX(Volume->FatType))
    {
        Volume->BytesPerSector = 512;
        Volume->SectorsPerCluster = SWAPD(FatXVolumeBootSector->SectorsPerCluster);
        Volume->FatSectorStart = (4096 / Volume->BytesPerSector);
        Volume->ActiveFatSectorStart = Volume->FatSectorStart;
        Volume->NumberOfFats = 1;
        FatSize = (ULONG)(PartitionSectorCount / Volume->SectorsPerCluster *
                  (Volume->FatType == FATX16 ? 2 : 4));
        Volume->SectorsPerFat = (((FatSize + 4095) / 4096) * 4096) / Volume->BytesPerSector;

        Volume->RootDirSectorStart = Volume->FatSectorStart + Volume->NumberOfFats * Volume->SectorsPerFat;
        Volume->RootDirSectors = FatXVolumeBootSector->SectorsPerCluster;

        Volume->DataSectorStart = Volume->RootDirSectorStart + Volume->RootDirSectors;
    }
    else if (Volume->FatType != FAT32)
    {
        Volume->BytesPerSector = FatVolumeBootSector->BytesPerSector;
        Volume->SectorsPerCluster = FatVolumeBootSector->SectorsPerCluster;
        Volume->FatSectorStart = FatVolumeBootSector->ReservedSectors;
        Volume->ActiveFatSectorStart = Volume->FatSectorStart;
        Volume->NumberOfFats = FatVolumeBootSector->NumberOfFats;
        Volume->SectorsPerFat = FatVolumeBootSector->SectorsPerFat;

        Volume->RootDirSectorStart = Volume->FatSectorStart + Volume->NumberOfFats * Volume->SectorsPerFat;
        Volume->RootDirSectors = ((FatVolumeBootSector->RootDirEntries * 32) + (Volume->BytesPerSector - 1)) / Volume->BytesPerSector;

        Volume->DataSectorStart = Volume->RootDirSectorStart + Volume->RootDirSectors;
    }
    else
    {
        Volume->BytesPerSector = Fat32VolumeBootSector->BytesPerSector;
        Volume->SectorsPerCluster = Fat32VolumeBootSector->SectorsPerCluster;
        Volume->FatSectorStart = Fat32VolumeBootSector->ReservedSectors;
        Volume->ActiveFatSectorStart = Volume->FatSectorStart +
                                       ((Fat32VolumeBootSector->ExtendedFlags & 0x80) ? ((Fat32VolumeBootSector->ExtendedFlags & 0x0f) * Fat32VolumeBootSector->SectorsPerFatBig) : 0);
        Volume->NumberOfFats = Fat32VolumeBootSector->NumberOfFats;
        Volume->SectorsPerFat = Fat32VolumeBootSector->SectorsPerFatBig;

        Volume->RootDirStartCluster = Fat32VolumeBootSector->RootDirStartCluster;
        Volume->DataSectorStart = Volume->FatSectorStart + Volume->NumberOfFats * Volume->SectorsPerFat;

        //
        // Check version
        // we only work with version 0
        //
        if (Fat32VolumeBootSector->FileSystemVersion != 0)
        {
            FileSystemError("FreeLoader is too old to work with this FAT32 filesystem.\nPlease update FreeLoader.");
            return FALSE;
        }
    }

    return TRUE;
}