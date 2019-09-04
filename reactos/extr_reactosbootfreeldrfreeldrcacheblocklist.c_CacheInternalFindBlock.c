#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_9__ {int /*<<< orphan*/  Flink; } ;
struct TYPE_8__ {scalar_t__ BlockNumber; TYPE_3__ ListEntry; int /*<<< orphan*/  AccessCount; } ;
struct TYPE_7__ {TYPE_3__ CacheBlockHead; } ;
typedef  TYPE_1__* PCACHE_DRIVE ;
typedef  TYPE_2__* PCACHE_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_BLOCK ; 
 TYPE_2__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsListEmpty (TYPE_3__*) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

PCACHE_BLOCK CacheInternalFindBlock(PCACHE_DRIVE CacheDrive, ULONG BlockNumber)
{
    PCACHE_BLOCK    CacheBlock = NULL;

    TRACE("CacheInternalFindBlock() BlockNumber = %d\n", BlockNumber);

    //
    // Make sure the block list has entries before I start searching it.
    //
    if (!IsListEmpty(&CacheDrive->CacheBlockHead))
    {
        //
        // Search the list and find the BIOS drive number
        //
        CacheBlock = CONTAINING_RECORD(CacheDrive->CacheBlockHead.Flink, CACHE_BLOCK, ListEntry);

        while (&CacheBlock->ListEntry != &CacheDrive->CacheBlockHead)
        {
            //
            // We found the block, so return it
            //
            if (CacheBlock->BlockNumber == BlockNumber)
            {
                //
                // Increment the blocks access count
                //
                CacheBlock->AccessCount++;

                return CacheBlock;
            }

            CacheBlock = CONTAINING_RECORD(CacheBlock->ListEntry.Flink, CACHE_BLOCK, ListEntry);
        }
    }

    return NULL;
}