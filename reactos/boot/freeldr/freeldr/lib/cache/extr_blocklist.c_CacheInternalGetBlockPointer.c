#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  BlockNumber; } ;
typedef  int /*<<< orphan*/  PCACHE_DRIVE ;
typedef  TYPE_1__* PCACHE_BLOCK ;

/* Variables and functions */
 TYPE_1__* CacheInternalAddBlockToCache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* CacheInternalFindBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheInternalOptimizeBlockList (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 

PCACHE_BLOCK CacheInternalGetBlockPointer(PCACHE_DRIVE CacheDrive, ULONG BlockNumber)
{
    PCACHE_BLOCK    CacheBlock = NULL;

    TRACE("CacheInternalGetBlockPointer() BlockNumber = %d\n", BlockNumber);

    CacheBlock = CacheInternalFindBlock(CacheDrive, BlockNumber);

    if (CacheBlock != NULL)
    {
        TRACE("Cache hit! BlockNumber: %d CacheBlock->BlockNumber: %d\n", BlockNumber, CacheBlock->BlockNumber);

        return CacheBlock;
    }

    TRACE("Cache miss! BlockNumber: %d\n", BlockNumber);

    CacheBlock = CacheInternalAddBlockToCache(CacheDrive, BlockNumber);

    // Optimize the block list so it has a LRU structure
    CacheInternalOptimizeBlockList(CacheDrive, CacheBlock);

    return CacheBlock;
}