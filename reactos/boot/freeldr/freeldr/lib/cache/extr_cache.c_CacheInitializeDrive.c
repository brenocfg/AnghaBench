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
typedef  int UCHAR ;
struct TYPE_10__ {int DriveNumber; int BytesPerSector; int BlockSize; int /*<<< orphan*/  CacheBlockHead; } ;
struct TYPE_9__ {int BytesPerSector; } ;
struct TYPE_8__ {struct TYPE_8__* BlockData; } ;
typedef  TYPE_1__* PCACHE_BLOCK ;
typedef  TYPE_2__ GEOMETRY ;
typedef  int /*<<< orphan*/  CACHE_DRIVE ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_BLOCK ; 
 TYPE_1__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CacheBlockCount ; 
 void* CacheManagerDataInvalid ; 
 TYPE_3__ CacheManagerDrive ; 
 void* CacheManagerInitialized ; 
 int CacheSizeCurrent ; 
 int CacheSizeLimit ; 
 void* FALSE ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListEntry ; 
 int MM_PAGE_SIZE ; 
 int MachDiskGetCacheableBlockCount (int) ; 
 int /*<<< orphan*/  MachDiskGetDriveGeometry (int,TYPE_2__*) ; 
 int /*<<< orphan*/  RemoveHeadList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  TAG_CACHE_BLOCK ; 
 int /*<<< orphan*/  TAG_CACHE_DATA ; 
 scalar_t__ TEMP_HEAP_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 void* TRUE ; 
 int TotalPagesInLookupTable ; 
 int min (int,scalar_t__) ; 

BOOLEAN CacheInitializeDrive(UCHAR DriveNumber)
{
    PCACHE_BLOCK    NextCacheBlock;
    GEOMETRY    DriveGeometry;

    // If we already have a cache for this drive then
    // by all means lets keep it, unless it is a removable
    // drive, in which case we'll invalidate the cache
    if ((CacheManagerInitialized) &&
        (DriveNumber == CacheManagerDrive.DriveNumber) &&
        (DriveNumber >= 0x80) &&
        (!CacheManagerDataInvalid))
    {
        return TRUE;
    }

    CacheManagerDataInvalid = FALSE;

    //
    // If we have already been initialized then free
    // the old data
    //
    if (CacheManagerInitialized)
    {
        CacheManagerInitialized = FALSE;

        TRACE("CacheBlockCount: %d\n", CacheBlockCount);
        TRACE("CacheSizeLimit: %d\n", CacheSizeLimit);
        TRACE("CacheSizeCurrent: %d\n", CacheSizeCurrent);
        //
        // Loop through and free the cache blocks
        //
        while (!IsListEmpty(&CacheManagerDrive.CacheBlockHead))
        {
            NextCacheBlock = CONTAINING_RECORD(RemoveHeadList(&CacheManagerDrive.CacheBlockHead),
                                               CACHE_BLOCK,
                                               ListEntry);

            FrLdrTempFree(NextCacheBlock->BlockData, TAG_CACHE_DATA);
            FrLdrTempFree(NextCacheBlock, TAG_CACHE_BLOCK);
        }
    }

    // Initialize the structure
    RtlZeroMemory(&CacheManagerDrive, sizeof(CACHE_DRIVE));
    InitializeListHead(&CacheManagerDrive.CacheBlockHead);
    CacheManagerDrive.DriveNumber = DriveNumber;
    if (!MachDiskGetDriveGeometry(DriveNumber, &DriveGeometry))
    {
        return FALSE;
    }
    CacheManagerDrive.BytesPerSector = DriveGeometry.BytesPerSector;

    // Get the number of sectors in each cache block
    CacheManagerDrive.BlockSize = MachDiskGetCacheableBlockCount(DriveNumber);

    CacheBlockCount = 0;
    CacheSizeCurrent = 0;
    CacheSizeLimit = TotalPagesInLookupTable / 8 * MM_PAGE_SIZE;
    CacheSizeLimit = min(CacheSizeLimit, TEMP_HEAP_SIZE - (128 * 1024));

    CacheManagerInitialized = TRUE;

    TRACE("Initializing BIOS drive 0x%x.\n", DriveNumber);
    TRACE("BytesPerSector: %d.\n", CacheManagerDrive.BytesPerSector);
    TRACE("BlockSize: %d.\n", CacheManagerDrive.BlockSize);
    TRACE("CacheSizeLimit: %d.\n", CacheSizeLimit);

    return TRUE;
}