#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_11__ {int BlockNumber; int /*<<< orphan*/  ListEntry; struct TYPE_11__* BlockData; } ;
struct TYPE_10__ {int BlockSize; int BytesPerSector; int /*<<< orphan*/  CacheBlockHead; int /*<<< orphan*/  DriveNumber; } ;
typedef  TYPE_1__* PCACHE_DRIVE ;
typedef  TYPE_2__* PCACHE_BLOCK ;
typedef  int /*<<< orphan*/  CACHE_BLOCK ;

/* Variables and functions */
 int CacheBlockCount ; 
 int /*<<< orphan*/  CacheInternalCheckCacheSizeLimits (TYPE_1__*) ; 
 int /*<<< orphan*/  CacheInternalDumpBlockList (TYPE_1__*) ; 
 int CacheSizeCurrent ; 
 int /*<<< orphan*/  DiskReadBuffer ; 
 void* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MachDiskReadLogicalSectors (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TAG_CACHE_BLOCK ; 
 int /*<<< orphan*/  TAG_CACHE_DATA ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 

PCACHE_BLOCK CacheInternalAddBlockToCache(PCACHE_DRIVE CacheDrive, ULONG BlockNumber)
{
    PCACHE_BLOCK    CacheBlock = NULL;

    TRACE("CacheInternalAddBlockToCache() BlockNumber = %d\n", BlockNumber);

    // Check the size of the cache so we don't exceed our limits
    CacheInternalCheckCacheSizeLimits(CacheDrive);

    // We will need to add the block to the
    // drive's list of cached blocks. So allocate
    // the block memory.
    CacheBlock = FrLdrTempAlloc(sizeof(CACHE_BLOCK), TAG_CACHE_BLOCK);
    if (CacheBlock == NULL)
    {
        return NULL;
    }

    // Now initialize the structure and
    // allocate room for the block data
    RtlZeroMemory(CacheBlock, sizeof(CACHE_BLOCK));
    CacheBlock->BlockNumber = BlockNumber;
    CacheBlock->BlockData = FrLdrTempAlloc(CacheDrive->BlockSize * CacheDrive->BytesPerSector,
                                           TAG_CACHE_DATA);
    if (CacheBlock->BlockData ==NULL)
    {
        FrLdrTempFree(CacheBlock, TAG_CACHE_BLOCK);
        return NULL;
    }

    // Now try to read in the block
    if (!MachDiskReadLogicalSectors(CacheDrive->DriveNumber, (BlockNumber * CacheDrive->BlockSize), CacheDrive->BlockSize, DiskReadBuffer))
    {
        FrLdrTempFree(CacheBlock->BlockData, TAG_CACHE_DATA);
        FrLdrTempFree(CacheBlock, TAG_CACHE_BLOCK);
        return NULL;
    }
    RtlCopyMemory(CacheBlock->BlockData, DiskReadBuffer, CacheDrive->BlockSize * CacheDrive->BytesPerSector);

    // Add it to our list of blocks managed by the cache
    InsertTailList(&CacheDrive->CacheBlockHead, &CacheBlock->ListEntry);

    // Update the cache data
    CacheBlockCount++;
    CacheSizeCurrent = CacheBlockCount * (CacheDrive->BlockSize * CacheDrive->BytesPerSector);

    CacheInternalDumpBlockList(CacheDrive);

    return CacheBlock;
}