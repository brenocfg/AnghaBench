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
typedef  int ULONG ;
struct TYPE_5__ {scalar_t__ FatType; } ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;

/* Variables and functions */
 scalar_t__ FAT12 ; 
 scalar_t__ FAT16 ; 
 scalar_t__ FAT32 ; 
 scalar_t__ FATX16 ; 
 scalar_t__ FATX32 ; 
 int FatCountClustersInChain (TYPE_1__*,int) ; 
 int /*<<< orphan*/  FatGetFatEntry (TYPE_1__*,int,int*) ; 
 int* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_FAT_CHAIN ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 

ULONG* FatGetClusterChainArray(PFAT_VOLUME_INFO Volume, ULONG StartCluster)
{
    ULONG    ClusterCount;
    ULONG        ArraySize;
    ULONG*    ArrayPointer;
    ULONG        Idx;

    TRACE("FatGetClusterChainArray() StartCluster = %d\n", StartCluster);

    ClusterCount = FatCountClustersInChain(Volume, StartCluster) + 1; // Lets get the 0x0ffffff8 on the end of the array
    ArraySize = ClusterCount * sizeof(ULONG);

    //
    // Allocate array memory
    //
    ArrayPointer = FrLdrTempAlloc(ArraySize, TAG_FAT_CHAIN);

    if (ArrayPointer == NULL)
    {
        return NULL;
    }

    //
    // Loop through and set array values
    //
    for (Idx=0; Idx<ClusterCount; Idx++)
    {
        //
        // Set current cluster
        //
        ArrayPointer[Idx] = StartCluster;

        //
        // Don't try to get next cluster for last cluster
        //
        if (((Volume->FatType == FAT12) && (StartCluster >= 0xff8)) ||
            ((Volume->FatType == FAT16 || Volume->FatType == FATX16) && (StartCluster >= 0xfff8)) ||
            ((Volume->FatType == FAT32 || Volume->FatType == FATX32) && (StartCluster >= 0x0ffffff8)))
        {
            Idx++;
            break;
        }

        //
        // Get next cluster
        //
        if (!FatGetFatEntry(Volume, StartCluster, &StartCluster))
        {
            FrLdrTempFree(ArrayPointer, TAG_FAT_CHAIN);
            return NULL;
        }
    }

    return ArrayPointer;
}