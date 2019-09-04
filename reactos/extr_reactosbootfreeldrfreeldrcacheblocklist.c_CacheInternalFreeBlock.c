#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Blink; } ;
struct TYPE_9__ {struct TYPE_9__* BlockData; TYPE_3__ ListEntry; scalar_t__ LockedInCache; } ;
struct TYPE_8__ {int BlockSize; int BytesPerSector; TYPE_3__ CacheBlockHead; } ;
typedef  TYPE_1__* PCACHE_DRIVE ;
typedef  TYPE_2__* PCACHE_BLOCK ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_BLOCK ; 
 TYPE_2__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CacheBlockCount ; 
 int CacheSizeCurrent ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IsListEmpty (TYPE_3__*) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  RemoveEntryList (TYPE_3__*) ; 
 int /*<<< orphan*/  TAG_CACHE_BLOCK ; 
 int /*<<< orphan*/  TAG_CACHE_DATA ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN CacheInternalFreeBlock(PCACHE_DRIVE CacheDrive)
{
    PCACHE_BLOCK    CacheBlockToFree;

    TRACE("CacheInternalFreeBlock()\n");

    // Get a pointer to the last item in the block list
    // that isn't forced to be in the cache and remove
    // it from the list
    CacheBlockToFree = CONTAINING_RECORD(CacheDrive->CacheBlockHead.Blink, CACHE_BLOCK, ListEntry);
    while (&CacheBlockToFree->ListEntry != &CacheDrive->CacheBlockHead && CacheBlockToFree->LockedInCache)
    {
        CacheBlockToFree = CONTAINING_RECORD(CacheBlockToFree->ListEntry.Blink, CACHE_BLOCK, ListEntry);
    }

    // No blocks left in cache that can be freed
    // so just return
    if (IsListEmpty(&CacheDrive->CacheBlockHead))
    {
        return FALSE;
    }

    RemoveEntryList(&CacheBlockToFree->ListEntry);

    // Free the block memory and the block structure
    FrLdrTempFree(CacheBlockToFree->BlockData, TAG_CACHE_DATA);
    FrLdrTempFree(CacheBlockToFree, TAG_CACHE_BLOCK);

    // Update the cache data
    CacheBlockCount--;
    CacheSizeCurrent = CacheBlockCount * (CacheDrive->BlockSize * CacheDrive->BytesPerSector);

    return TRUE;
}