#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {scalar_t__ SectorsPerCluster; scalar_t__ DataSectorStart; int BytesPerSector; scalar_t__ FatType; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FAT12 ; 
 scalar_t__ FAT16 ; 
 scalar_t__ FAT32 ; 
 scalar_t__ FATX16 ; 
 scalar_t__ FATX32 ; 
 int /*<<< orphan*/  FatGetFatEntry (TYPE_1__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  FatReadVolumeSectors (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN FatReadClusterChain(PFAT_VOLUME_INFO Volume, ULONG StartClusterNumber, ULONG NumberOfClusters, PVOID Buffer)
{
    ULONG        ClusterStartSector;

    TRACE("FatReadClusterChain() StartClusterNumber = %d NumberOfClusters = %d Buffer = 0x%x\n", StartClusterNumber, NumberOfClusters, Buffer);

    while (NumberOfClusters > 0)
    {

        //TRACE("FatReadClusterChain() StartClusterNumber = %d NumberOfClusters = %d Buffer = 0x%x\n", StartClusterNumber, NumberOfClusters, Buffer);
        //
        // Calculate starting sector for cluster
        //
        ClusterStartSector = ((StartClusterNumber - 2) * Volume->SectorsPerCluster) + Volume->DataSectorStart;

        //
        // Read cluster into memory
        //
        if (!FatReadVolumeSectors(Volume, ClusterStartSector, Volume->SectorsPerCluster, Buffer))
        {
            return FALSE;
        }

        //
        // Decrement count of clusters left to read
        //
        NumberOfClusters--;

        //
        // Increment buffer address by cluster size
        //
        Buffer = (PVOID)((ULONG_PTR)Buffer + (Volume->SectorsPerCluster * Volume->BytesPerSector));

        //
        // Get next cluster
        //
        if (!FatGetFatEntry(Volume, StartClusterNumber, &StartClusterNumber))
        {
            return FALSE;
        }

        //
        // If end of chain then break out of our cluster reading loop
        //
        if (((Volume->FatType == FAT12) && (StartClusterNumber >= 0xff8)) ||
            ((Volume->FatType == FAT16 || Volume->FatType == FATX16) && (StartClusterNumber >= 0xfff8)) ||
            ((Volume->FatType == FAT32 || Volume->FatType == FATX32) && (StartClusterNumber >= 0x0ffffff8)))
        {
            break;
        }
    }

    return TRUE;
}