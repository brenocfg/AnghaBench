#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_18__ {int /*<<< orphan*/  QuadPart; int /*<<< orphan*/  LowPart; int /*<<< orphan*/  HighPart; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_17__ {int /*<<< orphan*/  LowPart; int /*<<< orphan*/  HighPart; } ;
struct TYPE_24__ {TYPE_1__ EndingAddress; } ;
struct TYPE_23__ {scalar_t__ LowPart; scalar_t__ HighPart; } ;
struct TYPE_22__ {int /*<<< orphan*/  FileSystemType; } ;
struct TYPE_21__ {int /*<<< orphan*/  FileSystemType; } ;
struct TYPE_20__ {int /*<<< orphan*/  FileSystemType; } ;
struct TYPE_19__ {int DeviceId; } ;
typedef  TYPE_3__* PFAT_VOLUME_INFO ;
typedef  TYPE_4__* PFAT_BOOTSECTOR ;
typedef  TYPE_5__* PFATX_BOOTSECTOR ;
typedef  TYPE_6__* PFAT32_BOOTSECTOR ;
typedef  TYPE_7__ LARGE_INTEGER ;
typedef  TYPE_8__ FILEINFORMATION ;
typedef  int /*<<< orphan*/  FAT_VOLUME_INFO ;
typedef  int /*<<< orphan*/  DEVVTBL ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ ARC_STATUS ;

/* Variables and functions */
 scalar_t__ ArcGetFileInformation (int,TYPE_8__*) ; 
 scalar_t__ ArcRead (int,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ ArcSeek (int,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESUCCESS ; 
 int /*<<< orphan*/  const FatFuncTable ; 
 int /*<<< orphan*/  FatOpenVolume (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__** FatVolumes ; 
 TYPE_3__* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlEqualMemory (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  SECTOR_SIZE ; 
 int /*<<< orphan*/  SeekAbsolute ; 
 int /*<<< orphan*/  TAG_FAT_VOLUME ; 

const DEVVTBL* FatMount(ULONG DeviceId)
{
    PFAT_VOLUME_INFO Volume;
    UCHAR Buffer[512];
    PFAT_BOOTSECTOR BootSector = (PFAT_BOOTSECTOR)Buffer;
    PFAT32_BOOTSECTOR BootSector32 = (PFAT32_BOOTSECTOR)Buffer;
    PFATX_BOOTSECTOR BootSectorX = (PFATX_BOOTSECTOR)Buffer;
    FILEINFORMATION FileInformation;
    LARGE_INTEGER Position;
    ULONG Count;
    ULARGE_INTEGER SectorCount;
    ARC_STATUS Status;

    //
    // Allocate data for volume information
    //
    Volume = FrLdrTempAlloc(sizeof(FAT_VOLUME_INFO), TAG_FAT_VOLUME);
    if (!Volume)
        return NULL;
    RtlZeroMemory(Volume, sizeof(FAT_VOLUME_INFO));

    //
    // Read the BootSector
    //
    Position.HighPart = 0;
    Position.LowPart = 0;
    Status = ArcSeek(DeviceId, &Position, SeekAbsolute);
    if (Status != ESUCCESS)
    {
        FrLdrTempFree(Volume, TAG_FAT_VOLUME);
        return NULL;
    }
    Status = ArcRead(DeviceId, Buffer, sizeof(Buffer), &Count);
    if (Status != ESUCCESS || Count != sizeof(Buffer))
    {
        FrLdrTempFree(Volume, TAG_FAT_VOLUME);
        return NULL;
    }

    //
    // Check if BootSector is valid. If no, return early
    //
    if (!RtlEqualMemory(BootSector->FileSystemType, "FAT12   ", 8) &&
        !RtlEqualMemory(BootSector->FileSystemType, "FAT16   ", 8) &&
        !RtlEqualMemory(BootSector32->FileSystemType, "FAT32   ", 8) &&
        !RtlEqualMemory(BootSectorX->FileSystemType, "FATX", 4))
    {
        FrLdrTempFree(Volume, TAG_FAT_VOLUME);
        return NULL;
    }

    //
    // Determine sector count
    //
    Status = ArcGetFileInformation(DeviceId, &FileInformation);
    if (Status != ESUCCESS)
    {
        FrLdrTempFree(Volume, TAG_FAT_VOLUME);
        return NULL;
    }
    SectorCount.HighPart = FileInformation.EndingAddress.HighPart;
    SectorCount.LowPart = FileInformation.EndingAddress.LowPart;
    SectorCount.QuadPart /= SECTOR_SIZE;

    //
    // Keep device id
    //
    Volume->DeviceId = DeviceId;

    //
    // Really open the volume
    //
    if (!FatOpenVolume(Volume, BootSector, SectorCount.QuadPart))
    {
        FrLdrTempFree(Volume, TAG_FAT_VOLUME);
        return NULL;
    }

    //
    // Remember FAT volume information
    //
    FatVolumes[DeviceId] = Volume;

    //
    // Return success
    //
    return &FatFuncTable;
}