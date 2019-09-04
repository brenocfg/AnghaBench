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
struct TYPE_4__ {scalar_t__ FatType; } ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;

/* Variables and functions */
 scalar_t__ FAT12 ; 
 scalar_t__ FAT16 ; 
 scalar_t__ FAT32 ; 
 scalar_t__ FATX16 ; 
 scalar_t__ FATX32 ; 
 int /*<<< orphan*/  FatGetFatEntry (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 

ULONG FatCountClustersInChain(PFAT_VOLUME_INFO Volume, ULONG StartCluster)
{
    ULONG    ClusterCount = 0;

    TRACE("FatCountClustersInChain() StartCluster = %d\n", StartCluster);

    while (1)
    {
        //
        // If end of chain then break out of our cluster counting loop
        //
        if (((Volume->FatType == FAT12) && (StartCluster >= 0xff8)) ||
            ((Volume->FatType == FAT16 || Volume->FatType == FATX16) && (StartCluster >= 0xfff8)) ||
            ((Volume->FatType == FAT32 || Volume->FatType == FATX32) && (StartCluster >= 0x0ffffff8)))
        {
            break;
        }

        //
        // Increment count
        //
        ClusterCount++;

        //
        // Get next cluster
        //
        if (!FatGetFatEntry(Volume, StartCluster, &StartCluster))
        {
            return 0;
        }
    }

    TRACE("FatCountClustersInChain() ClusterCount = %d\n", ClusterCount);

    return ClusterCount;
}