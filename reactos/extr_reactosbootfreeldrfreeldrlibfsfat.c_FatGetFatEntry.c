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
typedef  int USHORT ;
typedef  int ULONG ;
typedef  int UINT32 ;
struct TYPE_4__ {int BytesPerSector; int FatType; int ActiveFatSectorStart; } ;
typedef  int PUCHAR ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
#define  FAT12 132 
#define  FAT16 131 
#define  FAT32 130 
#define  FATX16 129 
#define  FATX32 128 
 int /*<<< orphan*/  FatReadVolumeSectors (TYPE_1__*,int,int,int) ; 
 int FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (int,int /*<<< orphan*/ ) ; 
 int SWAPD (int) ; 
 int SWAPW (int) ; 
 int /*<<< orphan*/  TAG_FAT_BUFFER ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN FatGetFatEntry(PFAT_VOLUME_INFO Volume, ULONG Cluster, ULONG* ClusterPointer)
{
    ULONG        fat = 0;
    UINT32        FatOffset;
    UINT32        ThisFatSecNum;
    UINT32        ThisFatEntOffset;
    ULONG SectorCount;
    PUCHAR ReadBuffer;
    BOOLEAN Success = TRUE;

    //TRACE("FatGetFatEntry() Retrieving FAT entry for cluster %d.\n", Cluster);

    // We need a buffer for 2 sectors
    ReadBuffer = FrLdrTempAlloc(2 * Volume->BytesPerSector, TAG_FAT_BUFFER);
    if (!ReadBuffer)
    {
        return FALSE;
    }

    switch(Volume->FatType)
    {
    case FAT12:

        FatOffset = Cluster + (Cluster / 2);
        ThisFatSecNum = Volume->ActiveFatSectorStart + (FatOffset / Volume->BytesPerSector);
        ThisFatEntOffset = (FatOffset % Volume->BytesPerSector);

        TRACE("FatOffset: %d\n", FatOffset);
        TRACE("ThisFatSecNum: %d\n", ThisFatSecNum);
        TRACE("ThisFatEntOffset: %d\n", ThisFatEntOffset);

        if (ThisFatEntOffset == (Volume->BytesPerSector - 1))
        {
            SectorCount = 2;
        }
        else
        {
            SectorCount = 1;
        }

        if (!FatReadVolumeSectors(Volume, ThisFatSecNum, SectorCount, ReadBuffer))
        {
            Success = FALSE;
            break;
        }

        fat = *((USHORT *) (ReadBuffer + ThisFatEntOffset));
        fat = SWAPW(fat);
        if (Cluster & 0x0001)
            fat = fat >> 4;    /* Cluster number is ODD */
        else
            fat = fat & 0x0FFF;    /* Cluster number is EVEN */

        break;

    case FAT16:
    case FATX16:

        FatOffset = (Cluster * 2);
        ThisFatSecNum = Volume->ActiveFatSectorStart + (FatOffset / Volume->BytesPerSector);
        ThisFatEntOffset = (FatOffset % Volume->BytesPerSector);

        if (!FatReadVolumeSectors(Volume, ThisFatSecNum, 1, ReadBuffer))
        {
            Success = FALSE;
            break;
        }

        fat = *((USHORT *) (ReadBuffer + ThisFatEntOffset));
        fat = SWAPW(fat);

        break;

    case FAT32:
    case FATX32:

        FatOffset = (Cluster * 4);
        ThisFatSecNum = Volume->ActiveFatSectorStart + (FatOffset / Volume->BytesPerSector);
        ThisFatEntOffset = (FatOffset % Volume->BytesPerSector);

        if (!FatReadVolumeSectors(Volume, ThisFatSecNum, 1, ReadBuffer))
        {
            return FALSE;
        }

        // Get the fat entry
        fat = (*((ULONG *) (ReadBuffer + ThisFatEntOffset))) & 0x0FFFFFFF;
        fat = SWAPD(fat);

        break;

    default:
        ERR("Unknown FAT type %d\n", Volume->FatType);
        Success = FALSE;
        break;
    }

    //TRACE("FAT entry is 0x%x.\n", fat);

    FrLdrTempFree(ReadBuffer, TAG_FAT_BUFFER);

    *ClusterPointer = fat;

    return Success;
}