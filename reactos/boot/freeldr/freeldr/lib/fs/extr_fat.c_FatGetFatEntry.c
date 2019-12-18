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
struct TYPE_4__ {int FatType; int BytesPerSector; } ;
typedef  int* PUINT32 ;
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
 int FatGetFatSector (TYPE_1__*,int) ; 
 int SWAPD (int) ; 
 int SWAPW (int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOLEAN FatGetFatEntry(PFAT_VOLUME_INFO Volume, UINT32 Cluster, PUINT32 ClusterPointer)
{
    UINT32 FatOffset, ThisFatSecNum, ThisFatEntOffset, fat;
    PUCHAR ReadBuffer;

    TRACE("FatGetFatEntry() Retrieving FAT entry for cluster %d.\n", Cluster);

    switch(Volume->FatType)
    {
    case FAT12:

        FatOffset = Cluster + (Cluster / 2);
        ThisFatSecNum = FatOffset / Volume->BytesPerSector;
        ThisFatEntOffset = (FatOffset % Volume->BytesPerSector);

        TRACE("FatOffset: %d\n", FatOffset);
        TRACE("ThisFatSecNum: %d\n", ThisFatSecNum);
        TRACE("ThisFatEntOffset: %d\n", ThisFatEntOffset);

        // The cluster pointer can span within two sectors, but the FatGetFatSector function
        // reads 4 sectors most times, except when we are at the edge of FAT cache
        // and/or FAT region on the disk. For FAT12 the whole FAT would be cached so
        // there will be no situation when the first sector is at the end of the cache
        // and the next one is in the beginning

        ReadBuffer = FatGetFatSector(Volume, ThisFatSecNum);
        if (!ReadBuffer)
        {
            return FALSE;
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
        ThisFatSecNum = FatOffset / Volume->BytesPerSector;
        ThisFatEntOffset = (FatOffset % Volume->BytesPerSector);

        ReadBuffer = FatGetFatSector(Volume, ThisFatSecNum);
        if (!ReadBuffer)
        {
            return FALSE;
        }

        fat = *((USHORT *) (ReadBuffer + ThisFatEntOffset));
        fat = SWAPW(fat);

        break;

    case FAT32:
    case FATX32:

        FatOffset = (Cluster * 4);
        ThisFatSecNum = FatOffset / Volume->BytesPerSector;
        ThisFatEntOffset = (FatOffset % Volume->BytesPerSector);

        ReadBuffer = FatGetFatSector(Volume, ThisFatSecNum);
        if (!ReadBuffer)
        {
            return FALSE;
        }

        // Get the fat entry
        fat = (*((ULONG *) (ReadBuffer + ThisFatEntOffset))) & 0x0FFFFFFF;
        fat = SWAPD(fat);

        break;

    default:
        ERR("Unknown FAT type %d\n", Volume->FatType);
        return FALSE;
    }

    TRACE("FAT entry is 0x%x.\n", fat);

    *ClusterPointer = fat;

    return TRUE;
}