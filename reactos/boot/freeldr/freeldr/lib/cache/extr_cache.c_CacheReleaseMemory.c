#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int BlockSize; int BytesPerSector; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CacheInternalFreeBlock (TYPE_1__*) ; 
 TYPE_1__ CacheManagerDrive ; 
 scalar_t__ CacheManagerInitialized ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

BOOLEAN CacheReleaseMemory(ULONG MinimumAmountToRelease)
{
    ULONG                AmountReleased;

    TRACE("CacheReleaseMemory() MinimumAmountToRelease = %d\n", MinimumAmountToRelease);

    // If we aren't initialized yet then they can't do this
    if (CacheManagerInitialized == FALSE)
    {
        return FALSE;
    }

    // Loop through and try to free the requested amount of memory
    for (AmountReleased=0; AmountReleased<MinimumAmountToRelease; )
    {
        // Try to free a block
        // If this fails then break out of the loop
        if (!CacheInternalFreeBlock(&CacheManagerDrive))
        {
            break;
        }

        // It succeeded so increment the amount of memory we have freed
        AmountReleased += CacheManagerDrive.BlockSize * CacheManagerDrive.BytesPerSector;
    }

    // Return status
    return (AmountReleased >= MinimumAmountToRelease);
}