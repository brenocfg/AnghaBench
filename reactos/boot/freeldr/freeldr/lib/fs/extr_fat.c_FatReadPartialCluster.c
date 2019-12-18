#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_4__ {int SectorsPerCluster; int DataSectorStart; int BytesPerSector; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int PUCHAR ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FatReadVolumeSectors (TYPE_1__*,int,int,int) ; 
 int FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_FAT_BUFFER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int) ; 

BOOLEAN FatReadPartialCluster(PFAT_VOLUME_INFO Volume, ULONG ClusterNumber, ULONG StartingOffset, ULONG Length, PVOID Buffer)
{
    ULONG        ClusterStartSector;
    ULONG SectorOffset, ReadSize, SectorCount;
    PUCHAR ReadBuffer;
    BOOLEAN Success = FALSE;

    //TRACE("FatReadPartialCluster() ClusterNumber = %d StartingOffset = %d Length = %d Buffer = 0x%x\n", ClusterNumber, StartingOffset, Length, Buffer);

    ClusterStartSector = ((ClusterNumber - 2) * Volume->SectorsPerCluster) + Volume->DataSectorStart;

    // This is the offset of the data in sectors
    SectorOffset = (StartingOffset / Volume->BytesPerSector);
    StartingOffset %= Volume->BytesPerSector;

    // Calculate how many sectors we need to read
    SectorCount = (StartingOffset + Length + Volume->BytesPerSector - 1) / Volume->BytesPerSector;

    // Calculate rounded up read size
    ReadSize = SectorCount * Volume->BytesPerSector;

    ReadBuffer = FrLdrTempAlloc(ReadSize, TAG_FAT_BUFFER);
    if (!ReadBuffer)
    {
        return FALSE;
    }

    if (FatReadVolumeSectors(Volume, ClusterStartSector + SectorOffset, SectorCount, ReadBuffer))
    {
        memcpy(Buffer, ReadBuffer + StartingOffset, Length);
        Success = TRUE;
    }

    FrLdrTempFree(ReadBuffer, TAG_FAT_BUFFER);

    return Success;
}